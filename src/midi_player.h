#ifndef MIDI_PLAYER_H
#define MIDI_PLAYER_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Initialize the MIDI player system.
 * Call once at program start.
 * Returns 0 on success, -1 on failure.
 */
int midi_player_init(void);

/**
 * Start playing a MIDI file.
 * If another file is already playing, it will be stopped first.
 * Returns 0 on success, -1 if the file cannot be opened or parsed.
 */
int midi_player_start(const char *file_path);

/**
 * Stop the currently playing MIDI file (if any).
 */
void midi_player_stop(void);

/**
 * Check if a MIDI file is currently playing.
 * Returns 1 if playing, 0 otherwise.
 */
int midi_player_is_playing(void);

/**
 * Shutdown the MIDI player system.
 * Call at program exit.
 */
void midi_player_shutdown(void);

#ifdef __cplusplus
}
#endif

#endif /* MIDI_PLAYER_H */
