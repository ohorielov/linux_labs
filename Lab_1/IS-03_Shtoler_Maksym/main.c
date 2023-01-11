#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct WavHeader {
    // RIFF
    char chunkId[4];
    uint32_t chunkSize;
    uint32_t format;

    // fmt
    char subchunk1Id[3];
    uint32_t subchunk1Size;
    uint16_t audioFormat;
    uint16_t numChannels;
    uint32_t sampleRate;
    uint32_t byteRate;
    uint16_t blockAlign;
    uint16_t bitsPerSample;
} WavHeader;

typedef struct WavDataHeader {
    char chunkId[4];
    uint32_t subchunk2Size;
} WavDataHeader;

int main()
{
    const char* inputName = "../Master Of Puppets.wav";
    const char* outputName = "../Master Of Puppets Edited.wav";
    float value;

    WavHeader wavHeader;
    FILE* input = fopen(inputName, "r");
    FILE* output = fopen(outputName, "w");
    if (input == NULL || output == NULL) {
        printf("ERROR: Couldn't open file!\n");
        return 1;
    }

    printf("Enter value to multiply samples on: ");
    scanf("%f", &value);


    fread(&wavHeader, sizeof(WavHeader), 1, input);
    if (strncmp(wavHeader.chunkId, "RIFF", 4) != 0 || strncmp(wavHeader.subchunk1Id, "fmt", 3) != 0) {
        printf("ERROR: Something went wrong!\n");
        return 1;
    }
    fwrite(&wavHeader, sizeof(WavHeader), 1, output);

    if (wavHeader.subchunk1Size > 16) {
        long externalDataSize = wavHeader.subchunk1Size - 16;
        char* externalData = malloc(externalDataSize);
        fread(externalData, externalDataSize, 1, input);
        fwrite(externalData, externalDataSize, 1, output);
        free(externalData);
    }

    WavDataHeader wavDataHeader;
    fread(&wavDataHeader, sizeof(WavDataHeader), 1, input);
    fwrite(&wavDataHeader, sizeof(WavDataHeader), 1, output);
    
    if (wavHeader.bitsPerSample == 16) {
        int16_t sample;
        while(fread(&sample, sizeof(int16_t), 1, input)) {
            sample *= value;
            fwrite(&sample, sizeof(int16_t), 1, output);
        }
    } else if (wavHeader.bitsPerSample == 32) {
        int32_t sample;
        while(fread(&sample, sizeof(int32_t), 1, input)) {
            sample *= value;
            fwrite(&sample, sizeof(int32_t), 1, output);
        }
    }

    printf("Done!\n");
    return 0;
}