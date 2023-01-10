#include "WavFile.h"



void printWavData(struct WAVHEADER wh)
{
    printf("ChunkId: %.4s\n", wh.chunkId);
    printf("ChunkSize: %u\n", wh.chunkSize);
    printf("Format: %.4s\n", wh.format);
    printf("SubchunkId1: %.4s\n", wh.subchunkId1);
    printf("SubchunkSize1: %u\n", wh.subchunkSize1);
    printf("AudioFormat: %u\n", wh.audioFormat);
    printf("NumChannels: %u\n", wh.numChannels);
    printf("SampleRate: %u\n", wh.sampleRate);
    printf("ByteRate: %u\n", wh.byteRate);
    printf("BlockAlign: %u\n", wh.blockAlign);
    printf("BitsPerSample: %u\n", wh.bitsPerSample);
    printf("SubchunkId2: %.4s\n", wh.subchunkId2);
    printf("SubchunkSize2: %u\n\n", wh.subchunkSize2);
};

void modifyVolume(FILE* input, FILE* output)
{
    float percent;
    printf("How much louder song do you want (in %%)\n");
    scanf("%f", &percent);
    
    int16_t sample;
    while (fread(&sample, sizeof(int16_t), 1, input))
    {
        sample *= (1 + percent/100);
        fwrite(&sample, sizeof(int16_t), 1, output); 
    }
    
    printf("Done!\n");

};

