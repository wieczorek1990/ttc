#include "midi_player.h"

// Sound disabled — all functions are no-ops

extern "C" {

int midi_player_init(void)
{
    return 0;
}

int midi_player_start(const char* file_path)
{
    (void)file_path;
    return 0;
}

void midi_player_stop(void)
{
}

int midi_player_is_playing(void)
{
    return 0;
}

void midi_player_shutdown(void)
{
}

} // extern "C"
