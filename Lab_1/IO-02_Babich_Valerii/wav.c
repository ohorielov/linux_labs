#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <malloc.h>

#include "wav.h"

#define RIFF_SIZE sizeof(struct wavRIFF)
#define FMT_SIZE sizeof(struct wavFmt)
#define DATA_HEADER_SIZE sizeof(struct wavDataHeader) - sizeof(uint8_t*)
#define AUDIO_SIZE(wav) wav->dataHeader.subchunk2Size
#define WAV_HEADER_SIZE RIFF_SIZE + FMT_SIZE + DATA_HEADER_SIZE

struct wav* wav_open(const uint8_t* file) {
    struct wav *currentWav = (struct wav*) malloc(sizeof(struct wav));
    FILE *wavFile;

    if ((wavFile = fopen(file, "rb")) == NULL) {
        printf("The file does not exist\n");
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

void wav_create(struct wav* wav, const uint8_t* file) {
    if (wav == NULL) {
       return; 
    }
    
    FILE *wavFile = fopen(file, "wb");

    fwrite(wav, WAV_HEADER_SIZE, 1, wavFile);
    fwrite(wav->dataHeader.wavData, AUDIO_SIZE(wav), 1, wavFile);

    fclose(wavFile);
}

void change_volume(struct wav* wav, int8_t value, bool isIncrease) {
    if (wav == NULL || value == 0) {
        return;
    }

    for (uint32_t i = 0; i < AUDIO_SIZE(wav); i++) {
        int8_t changedSound = (int8_t) (isIncrease) ? (wav->dataHeader.wavData[i] * value)
            : (wav->dataHeader.wavData[i] / value);
        if (changedSound > INT8_MAX) {
            changedSound = INT8_MAX;
        }
        else if (changedSound < INT8_MIN) {
            changedSound = INT8_MIN;
        }
        wav->dataHeader.wavData[i] = changedSound;
    }
}

