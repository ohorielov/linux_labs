#include "s_wavFileData.h"
#include <stdint.h>
#include <stdio.h>

void printWavFileData(s_wavFileData *wavFileData)
{
    printf("ChunkId: %.4s\n", wavFileData->chunkId);
    printf("ChunkSize: %u\n", wavFileData->chunkSize);
    printf("Format: %.4s\n", wavFileData->format);
    printf("SubchunkId1: %.4s\n", wavFileData->subchunkId1);
    printf("SubchunkSize1: %u\n", wavFileData->subchunkSize1);
    printf("AudioFormat: %u\n", wavFileData->audioFormat);
    printf("NumChannels: %u\n", wavFileData->numChannels);
    printf("SampleRate: %u\n", wavFileData->sampleRate);
    printf("ByteRate: %u\n", wavFileData->byteRate);
    printf("BlockAlign: %u\n", wavFileData->blockAlign);
    printf("BitsPerSample: %u\n", wavFileData->bitsPerSample);
    printf("SubchunkId2: %.4s\n", wavFileData->subchunkId2);
    printf("SubchunkSize2: %u\n", wavFileData->subchunkSize2);
}

int readWavFileData(s_wavFileData *wavFileData, char filename[])
{
    FILE *inputWav = fopen(filename, "r");
    if (inputWav == NULL) {
        printf("Something wrong with input wav file...\n");
        return 0;
    }

    fread(&wavFileData->chunkId, 4, 1, inputWav);
    fread(&wavFileData->chunkSize, 4, 1, inputWav);
    fread(&wavFileData->format, 4, 1, inputWav);
    fread(&wavFileData->subchunkId1, 4, 1, inputWav);
    fread(&wavFileData->subchunkSize1, 4, 1, inputWav);
    fread(&wavFileData->audioFormat, 2, 1, inputWav);
    fread(&wavFileData->numChannels, 2, 1, inputWav);
    fread(&wavFileData->sampleRate, 4, 1, inputWav);
    fread(&wavFileData->byteRate, 4, 1, inputWav);
    fread(&wavFileData->blockAlign, 2, 1, inputWav);
    fread(&wavFileData->bitsPerSample, 2, 1, inputWav);
    fread(&wavFileData->subchunkId2, 4, 1, inputWav);
    fread(&wavFileData->subchunkSize2, 4, 1, inputWav);
    
    wavFileData->data = *(uint16_t*)malloc(wavFileData->subchunkSize2);
    fread(&wavFileData->data, wavFileData->subchunkSize2, 1, inputWav);

    fclose(inputWav);
}
