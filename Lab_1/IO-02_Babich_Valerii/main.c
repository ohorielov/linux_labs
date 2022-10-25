#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <malloc.h>

#include "wav.h"

int32_t main(int32_t argc, char *argv[]) {
    struct wav* music = wav_open("Master Of Puppets.wav");
 
    change_volume(music, 3, true);
    wav_create(music, "True Master Of Puppets.wav");

    free(music);

    return 0;
}