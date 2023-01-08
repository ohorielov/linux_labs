#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <math.h>

typedef struct{
    uint8_t _chunkID[4];
    uint32_t _ChunkSize;
    uint8_t _Format[4];
    uint8_t _Subchunk1ID[4];
    uint32_t _Subchunk1Size;
    uint16_t _AudioFormat;
    uint16_t _NumChannels;
    uint32_t _SampleRate;
    uint32_t _ByteRate;
    uint16_t _ByteAlign;
    uint16_t _BitsPerSample;
    uint8_t _Subchunk2ID[4];
    uint32_t _Subchunk2Size;
    uint16_t* _Data;
} __attribute__((packed)) wav;
    