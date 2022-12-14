#include < math.h >
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

struct WAVHEADER
{
    char chunkId[4];

    unsigned long chunkSize;

    char format[4];

    char subchunk1Id[4];

    unsigned long subchunk1Size;

    unsigned short audioFormat;

    unsigned short numChannels;

    unsigned long sampleRate;

    unsigned long byteRate;

    unsigned short blockAlign;

    unsigned short bitsPerSample;

    char subchunk2Id[4];

    unsigned long subchunk2Size;

};

const int h_size = 44;

int main()
{
    FILE* input = fopen("c:\\Master Of Puppets.wav", "rb");

    if (input == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }
    
    FILE* output = fopen("c:\\Master Of Puppets_Edited5.wav", "wb");
    if (output == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }
    
    float factor = 5;
    WAVHEADER header;

    fread(&header, h_size, 1, input);

    printf_s("Sample rate: %d\n", header.sampleRate);
    printf_s("Channels: %d\n", header.numChannels);
    printf_s("Bits per sample: %d\n", header.bitsPerSample);

    float fDurationSeconds = 1.f * header.subchunk2Size / (header.bitsPerSample / 8) / header.numChannels / header.sampleRate;
    int iDurationMinutes = (int)floor(fDurationSeconds) / 60;
    fDurationSeconds = fDurationSeconds - (iDurationMinutes * 60);
    printf_s("Duration: %02d:%02.f\n", iDurationMinutes, fDurationSeconds);

    fwrite(&header, h_size, 1, output);
  
    int16_t sample;
    while (fread(&sample, sizeof(int16_t), 1, input))
    {
        sample *= factor;
        fwrite(&sample, sizeof(int16_t), 1, output); 
    }
    
    fclose(input);
    fclose(output);
}
