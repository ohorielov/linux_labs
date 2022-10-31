#include "wav.h"

#include <stdio.h>
#include <stdlib.h>

// first argument - volume factor (0.0 - 1.0)
int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("One argument expected!");
        exit(EXIT_FAILURE);
    }

    char *inputPath = "../Master Of Puppets.wav";
    char *outputPath = "../output.wav";

    Wav *wav = WavOpen(inputPath);
    if (!wav) {
        printf("Can't open wav file!\n");
        exit(EXIT_FAILURE);
    }

    WAV_INFO("Sample rate: ", SampleRate);
    WAV_INFO("Byte rate: ", ByteRate);

    WavSetVolume(wav, atof(argv[1]));
    WavWrite(wav, outputPath);

    WavFree(wav);

    exit(EXIT_SUCCESS);
}
