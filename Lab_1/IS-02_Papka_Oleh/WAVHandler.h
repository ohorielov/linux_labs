#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>


#define riffSize 12
#define fmtChunkSize 24
#define dataChunkSize 8
#define WAVMetadataSize (riffSize + fmtChunkSize + dataChunkSize)

typedef struct
{
    uint32_t chunkID;
    uint32_t chunkSize;
    uint32_t format;
} RIFF;

typedef struct 
{
    uint32_t subChunk1ID;
    uint32_t subChunk1Size;
    uint16_t audioFormat;
    uint16_t numChannels;
    uint32_t sampleRate;
    uint32_t byteRate;
    uint16_t blockAlign;
    uint16_t bitsPerSample;
} FMTSubChunk;

typedef struct
{
    uint32_t subChunk2ID;
    uint32_t subChunk2Size;
    uint8_t *data;
} DataSubChunk;

typedef struct
{
    RIFF riff;
    FMTSubChunk fmtSubChunk;
    DataSubChunk dataSubChunk;
} WAV;

WAV* loadWAVFile(const char*);
void handleWAV(WAV*, const char*);
void releaseMemory(WAV*);
