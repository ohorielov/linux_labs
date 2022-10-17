#include "stdint.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

#ifndef LAB_1_WAVE_H
#define LAB_1_WAVE_H

typedef struct{

    uint32_t id;
    uint32_t size;
    uint32_t format;

    uint32_t subchunk1Id;
    uint32_t subchunk1Size;
    uint16_t audioFormat;
    uint16_t numChannels;
    uint32_t sampleRate;
    uint32_t byteRate;
    uint16_t blockAlign;
    uint16_t bitsPerSample;

    uint32_t subchunk2Id;
    uint32_t subchunk2Size;
    uint8_t *dataSize;

} WAV_HEADER;

WAV_HEADER* openFile(char *filename);
void changeVolume(WAV_HEADER* header, char* filename );

#endif //LAB_1_WAVE_H
