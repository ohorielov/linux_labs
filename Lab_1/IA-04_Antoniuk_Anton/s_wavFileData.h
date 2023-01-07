#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
    char chunkId[4];
    uint32_t chunkSize;
    char format[4];
    char subchunkId1[4];
    uint32_t subchunkSize1;
    uint8_t audioFormat;
    uint8_t numChannels;
    uint32_t sampleRate;
    uint32_t byteRate;
    uint8_t blockAlign;
    uint8_t bitsPerSample;
    char subchunkId2[4];
    uint32_t subchunkSize2;
    uint16_t data;
} __attribute__((packed)) s_wavFileData;