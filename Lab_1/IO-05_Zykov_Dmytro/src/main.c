#include <stdio.h>

#include "wav_reader.h"


int main(int argc, char **argv) {
    const char *path = "../Master Of Puppets.wav";

    wav_t wav;
    wav_load(&wav, path);

    wav_change_volume(&wav, 0.1);
    wav_save(&wav, "../output_file.wav");

    wav_clear(&wav);
    return 0;
}
