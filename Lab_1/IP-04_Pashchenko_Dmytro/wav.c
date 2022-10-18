#include "wav.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define RIFF_SIZE sizeof(struct wavRiff)
#define FMT_SIZE sizeof(struct wavFmt)
#define DATA_HEADER_SIZE sizeof(struct wavDataHeader) - sizeof(uint8_t*)
#define AUDIO_SIZE(wav) wav->dataHeader.subchunk2Size
#define WAV_HEADER_SIZE RIFF_SIZE + FMT_SIZE + DATA_HEADER_SIZE

struct wav* open_wav(const char* fileName) {
    struct wav *currentWav = (struct wav*) malloc(sizeof(struct wav));
    FILE *wavFile;

    if ((wavFile = fopen(fileName, "rb")) == NULL) {
        printf("File does not exist\n");
        return NULL;
    }

    fread(&currentWav->riff, RIFF_SIZE, 1, wavFile);
    fread(&currentWav->fmt, FMT_SIZE, 1, wavFile);
    fread(&currentWav->dataHeader, DATA_HEADER_SIZE, 1, wavFile);

    currentWav->dataHeader.wavData = (int8_t*)malloc(AUDIO_SIZE(currentWav));
    fread(currentWav->dataHeader.wavData, AUDIO_SIZE(currentWav), 1, wavFile);

    fclose(wavFile);

    return currentWav;
}

void change_volume(struct wav* someWav, char changeValue, bool isIncrease) {
    if (someWav == NULL || changeValue == 0) {
        return;
    }

    for (uint32_t i = 0; i < AUDIO_SIZE(someWav); i++) {
        int8_t changedSound;

        if (isIncrease) {
            changedSound = someWav->dataHeader.wavData[i] * changeValue;
        }

        if (!isIncrease) {
            changedSound = someWav->dataHeader.wavData[i] / changeValue;
        }

        if (changedSound > INT8_MAX) {
            changedSound = INT8_MAX;
        }

        if (changedSound < INT8_MIN) {
            changedSound = INT8_MIN;
        }

        someWav->dataHeader.wavData[i] = changedSound;
    }
}

void create_new_wav(struct wav* someWav, const char* fileName) {
    if (someWav == NULL) {
        return;
    }

    FILE *wavFile = fopen(fileName, "wb");

    fwrite(someWav, WAV_HEADER_SIZE, 1, wavFile);
    fwrite(someWav->dataHeader.wavData, AUDIO_SIZE(someWav), 1, wavFile);

    fclose(wavFile);
}
