#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <malloc.h>

#include "wav_handle.h"

int32_t main(int32_t argc, char *argv[]) {
    struct wav* music = wav_file_open("Master Of Puppets.wav");
 
    wav_change_volume(music, 3, false);
    wav_file_create(music, "Master Of Puppets_changed.wav");

    free(music);

    return 0;
}