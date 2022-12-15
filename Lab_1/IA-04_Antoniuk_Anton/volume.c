#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "wavFileData.c"

int main(int argc, char *argv[])
{
    if (argc != 4) {
        printf("Usage: ./volume in.wav out.wav dB\n");
        return 1;
    }
    printf("Before seg fault");
    char* inputWavFile = argv[1];
    printf("After seg fault");
    printf("Input file: %s", inputWavFile);
    char* outputWavFile = argv[2];
    printf("Input file: %s", outputWavFile);
    // float dB = atof(argv[3]);
    // printf("Input file: %f", dB);

    s_wavFileData *wavFileData;
    readWavFileData(wavFileData, "../Master Of Puppets.wav");
    printWavFileData(wavFileData);
}