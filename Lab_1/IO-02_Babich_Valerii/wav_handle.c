#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <malloc.h>

#include "wav_handle.h"

#define RIFF_SIZE sizeof(struct wavRiff)
#define FMT_SIZE sizeof(struct wavFmt)
#define DATA_HEADER_SIZE sizeof(struct wavDataHeader) - sizeof(uint8_t*)
#define AUDIO_SIZE(wav) wav->dataHeader.subchunk2Size
#define WAV_HEADER_SIZE RIFF_SIZE + FMT_SIZE + DATA_HEADER_SIZE

struct wav* wav_file_open(const uint8_t* fileName) {
    struct wav *currentWav = (struct wav*) malloc(sizeof(struct wav));
    FILE *wavFile;

    if ((wavFile = fopen(fileName, "rb")) == NULL) {
        printf("The file with such a name does not exist\n");
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

void wav_change_volume(struct wav* someWav, int8_t changeValue, bool isIncrease) {
    if (someWav == NULL || changeValue == 0) {
        return;
    }

    for (uint32_t i = 0; i < AUDIO_SIZE(someWav); i++) {
        int8_t changedSound = (int8_t) (isIncrease) ? (someWav->dataHeader.wavData[i] * changeValue)
            : (someWav->dataHeader.wavData[i] / changeValue);
        if (changedSound > INT8_MAX) {
            changedSound = INT8_MAX;
        }
        else if (changedSound < INT8_MIN) {
            changedSound = INT8_MIN;
        }
        someWav->dataHeader.wavData[i] = changedSound;
    }
}

void wav_file_create(struct wav* someWav, const uint8_t* fileName) {
    if (someWav == NULL) {
       return; 
    }
    
    FILE *wavFile = fopen(fileName, "wb");

    fwrite(someWav, WAV_HEADER_SIZE, 1, wavFile);
    fwrite(someWav->dataHeader.wavData, AUDIO_SIZE(someWav), 1, wavFile);

    fclose(wavFile);
}