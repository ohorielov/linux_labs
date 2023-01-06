#include "WAVHandler.h"
#include <math.h>


WAV* loadWAVFile(const char* name)
{
    WAV* wav = (WAV*)malloc(sizeof(WAV));
    
    FILE* file = fopen(name, "rb");
    if (file == NULL)
    {
        puts("Error opening the file");
        puts(name);
        exit(1);
    }

    fseek(file, 0L, SEEK_END);
    uint64_t fileSize = ftell(file);
    rewind(file);
    
    wav->dataSubChunk.data = (uint8_t*)malloc(fileSize);

    fread((uint8_t*)&wav->riff, riffSize, 1, file);
    fread((uint8_t*)&wav->fmtSubChunk, fmtChunkSize, 1, file);
    fread((uint8_t*)&wav->dataSubChunk, dataChunkSize, 1, file);
    fread(wav->dataSubChunk.data, fileSize - WAVMetadataSize, 1, file);
    
    fclose(file);

    return wav;
}

void handleWAV(WAV* wav, const char* name)
{
    FILE* file = fopen(name, "w");
    if (file == NULL)
    {
        puts("Error opening the file");
        puts(name);
        exit(1);
    }

    float multiplier = 0.01;

    fwrite((uint8_t*)&wav->riff, riffSize, 1, file);
    fwrite((uint8_t*)&wav->fmtSubChunk, fmtChunkSize, 1, file);
    fwrite((uint8_t*)&wav->dataSubChunk, dataChunkSize, 1, file);
    
    for (uint32_t i = 0; i < wav->dataSubChunk.subChunk2Size; ++i)
    {
        uint8_t tempVal = wav->dataSubChunk.data[i] * multiplier;
        double newVal = round(tempVal);

        tempVal = (uint8_t)newVal;
        fwrite(&tempVal, sizeof(uint8_t), 1, file);
    }
    
    fclose(file);
}

void releaseMemory(WAV* wav)
{
    free(wav->dataSubChunk.data);
    free(wav);
}