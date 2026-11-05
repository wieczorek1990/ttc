#include "midi_player.h"

#include <libremidi/libremidi.hpp>
#include <libremidi/reader.hpp>

#include <atomic>
#include <chrono>
#include <condition_variable>
#include <fstream>
#include <mutex>
#include <thread>
#include <vector>

// Internal state for MIDI playback
struct MidiPlayerState {
    std::unique_ptr<libremidi::midi_out> midiOut;
    std::thread playThread;
    std::atomic<bool> playing{false};
    std::atomic<bool> stopRequested{false};
    std::mutex stateMutex;
    std::condition_variable cv;

    // Parsed MIDI data
    std::vector<libremidi::track_event> mergedEvents;
    double endTime = 0.0;
    double ticksPerBeat = 0.0;
    double startingTempo = 120.0;
};

static MidiPlayerState g_state;

/**
 * Merge all tracks into a single sorted event list with absolute tick times.
 */
static void merge_tracks(
    const std::vector<libremidi::midi_track>& tracks,
    std::vector<libremidi::track_event>& merged)
{
    merged.clear();
    merged.reserve(1024);

    for (const auto& track : tracks) {
        for (const auto& event : track) {
            merged.push_back(event);
        }
    }

    // Sort by absolute tick
    std::sort(merged.begin(), merged.end(),
              [](const libremidi::track_event& a, const libremidi::track_event& b) {
                  return a.tick < b.tick;
              });
}

/**
 * Convert MIDI ticks to seconds using tempo information.
 * Simplified: uses starting tempo for the entire file.
 */
static double ticks_to_seconds(double ticks, double ticksPerBeat, double tempo)
{
    double beatDuration = 60.0 / tempo; // seconds per beat
    double tickDuration = beatDuration / ticksPerBeat; // seconds per tick
    return ticks * tickDuration;
}

/**
 * Background thread that plays MIDI events with timing.
 */
static void playback_thread(MidiPlayerState& state)
{
    if (!state.midiOut || !state.midiOut->is_port_open()) {
        state.playing = false;
        return;
    }

    state.playing = true;
    state.stopRequested = false;

    double ticksPerBeat = state.ticksPerBeat;
    double tempo = state.startingTempo;
    double beatDuration = 60.0 / tempo;
    double tickDuration = beatDuration / ticksPerBeat;

    auto startTime = std::chrono::steady_clock::now();

    for (const auto& event : state.mergedEvents) {
        if (state.stopRequested) {
            break;
        }

        // Calculate when this event should play
        double eventTime = event.tick * tickDuration;
        auto now = std::chrono::steady_clock::now();
        double elapsed = std::chrono::duration<double>(now - startTime).count();

        double sleepTime = eventTime - elapsed;
        if (sleepTime > 0.0) {
            // Check for stop request while waiting
            auto waitDuration = std::chrono::microseconds(static_cast<int64_t>(sleepTime * 1'000'000));
            std::unique_lock<std::mutex> lock(state.stateMutex);
            state.cv.wait_for(lock, waitDuration, [&state] { return state.stopRequested.load(); });
            if (state.stopRequested) break;
        }

        // Send the MIDI message (skip meta events for output)
        if (!event.m.is_meta_event() && !event.m.bytes.empty()) {
            state.midiOut->send_message(event.m.bytes.data(), event.m.bytes.size());
        }
    }

    // Send all notes off when done or stopped
    for (int ch = 0; ch < 16; ch++) {
        state.midiOut->send_message(libremidi::channel_events::note_off(ch, 0, 0));
    }

    state.playing = false;
    state.stopRequested = false;
    state.cv.notify_all();
}

extern "C" {

int midi_player_init(void)
{
    try {
        g_state.midiOut = std::make_unique<libremidi::midi_out>();
        return 0;
    } catch (...) {
        return -1;
    }
}

int midi_player_start(const char* file_path)
{
    if (!file_path || !g_state.midiOut) {
        return -1;
    }

    // Stop any currently playing file
    midi_player_stop();

    // Read the MIDI file
    std::ifstream file(file_path, std::ios::binary);
    if (!file.is_open()) {
        return -1;
    }

    std::vector<uint8_t> bytes;
    bytes.assign(std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>());
    file.close();

    // Parse the MIDI file
    libremidi::reader reader{true}; // use absolute ticks
    auto result = reader.parse(bytes);

    if (result == libremidi::reader::invalid) {
        return -1;
    }

    // Merge all tracks
    merge_tracks(reader.tracks, g_state.mergedEvents);

    g_state.endTime = reader.get_end_time();
    g_state.ticksPerBeat = reader.ticksPerBeat;
    g_state.startingTempo = reader.startingTempo;

    // Open the default MIDI output port
    libremidi::observer observer;
    auto outputPorts = observer.get_output_ports();

    if (outputPorts.empty()) {
        // No MIDI output ports available — this is common on systems without
        // a MIDI synthesizer. Return success anyway so the game doesn't break,
        // but playback will be silent.
        g_state.playing = false;
        return 0;
    }

    // Try to open the first available output port
    auto err = g_state.midiOut->open_port(outputPorts[0]);
    if (err.is_set()) {
        // Could not open port — return success so the game doesn't break
        g_state.playing = false;
        return 0;
    }

    // Start playback in a background thread
    g_state.stopRequested = false;
    g_state.playThread = std::thread(playback_thread, std::ref(g_state));

    return 0;
}

void midi_player_stop(void)
{
    if (g_state.playThread.joinable()) {
        g_state.stopRequested = true;
        g_state.cv.notify_all();
        g_state.playThread.join();
    }

    if (g_state.midiOut && g_state.midiOut->is_port_open()) {
        // Send all notes off
        for (int ch = 0; ch < 16; ch++) {
            g_state.midiOut->send_message(libremidi::channel_events::note_off(ch, 0, 0));
        }
        g_state.midiOut->close_port();
    }

    g_state.playing = false;
    g_state.stopRequested = false;
}

int midi_player_is_playing(void)
{
    return g_state.playing.load() ? 1 : 0;
}

void midi_player_shutdown(void)
{
    midi_player_stop();
    g_state.midiOut.reset();
}

} // extern "C"
