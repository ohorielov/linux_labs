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

    fread((uint8_t*)&wav->riff, 1, riffSize, file);
    fread((uint8_t*)&wav->fmtSubChunk, 1, fmtChunkSize, file);
    fread((uint8_t*)&wav->dataSubChunk, 1, dataChunkSize, file);
    fread(wav->dataSubChunk.data, 1, fileSize - WAVMetadataSize, file);
    
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

    fwrite((uint8_t*)&wav->riff, 1, riffSize, file);
    fwrite((uint8_t*)&wav->fmtSubChunk, 1, fmtChunkSize, file);
    fwrite((uint8_t*)&wav->dataSubChunk, 1, dataChunkSize, file);
    
    for (uint32_t i = 0; i < wav->dataSubChunk.subChunk2Size; ++i)
    {
        uint8_t tempVal = wav->dataSubChunk.data[i] * multiplier;
        double newVal = round(tempVal);

        if (newVal >= UINT8_MAX) 
            tempVal = UINT8_MAX;
         else if (newVal <= 0) 
            tempVal = 0;
         else 
            tempVal = (uint8_t)newVal;
        fwrite(&tempVal, 1, sizeof(uint8_t), file);
    }

    fclose(file);
}

void releaseMemory(WAV* wav)
{
    free(wav->dataSubChunk.data);
    free(wav);
}