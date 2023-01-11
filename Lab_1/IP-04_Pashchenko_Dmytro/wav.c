#include "wav.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define DATA_SUBCHUNK_SIZE sizeof(struct dataSubchunk) - sizeof(uint8_t*)

#define AUDIO_SIZE(wav) wav->data.subchunk2Size
#define WAV_HEADER_SIZE sizeof(struct riffChunk) + sizeof(struct fmtSubchunk) + DATA_SUBCHUNK_SIZE

struct wav* open_wav(const char* fileName) {
    struct wav *currentWav = (struct wav*) malloc(sizeof(struct wav));
    FILE *wavFile;

    if ((wavFile = fopen(fileName, "rb")) == NULL) {
        printf("File does not exist\n");
        return NULL;
    }

    fread(&currentWav->riff, sizeof(struct riffChunk), 1, wavFile);
    fread(&currentWav->fmt, sizeof(struct fmtSubchunk), 1, wavFile);
    fread(&currentWav->data, DATA_SUBCHUNK_SIZE, 1, wavFile);

    currentWav->data.wavData = (int8_t*)malloc(AUDIO_SIZE(currentWav));
    fread(currentWav->data.wavData, AUDIO_SIZE(currentWav), 1, wavFile);

    fclose(wavFile);

    return currentWav;
}

void change_volume(struct wav* someWav, char changeValue, bool isIncrease) {
    if (someWav == NULL || changeValue == 0) {
        return;
    }

    for (int i = 0; i < AUDIO_SIZE(someWav); i++) {
        int8_t changedSound = someWav->data.wavData[i];

        if (isIncrease) changedSound *= changeValue;
        if (!isIncrease) changedSound /= changeValue;

        if (changedSound > INT8_MAX) changedSound = INT8_MAX;
        if (changedSound < INT8_MIN) changedSound = INT8_MIN;

        someWav->data.wavData[i] = changedSound;
    }
}

void create_new_wav(struct wav* someWav, const char* fileName) {
    if (someWav == NULL) {
        return;
    }

    FILE *wavFile = fopen(fileName, "wb");

    fwrite(someWav, WAV_HEADER_SIZE, 1, wavFile);
    fwrite(someWav->data.wavData, AUDIO_SIZE(someWav), 1, wavFile);

    fclose(wavFile);
}
