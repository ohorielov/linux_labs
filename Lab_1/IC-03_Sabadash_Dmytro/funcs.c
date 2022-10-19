#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include "types.h"

#include "funcs.h"

#define BUF_SIZE 44

unsigned int convert2(const unsigned char *arr) {
    unsigned int result = arr[0] |  arr[1] << 8;
    return result;
}

unsigned int convert4(const unsigned char *arr) {
    unsigned int result = arr[0] |  arr[1] << 8 | arr[2] << 16 | arr[3] << 24;
    return result;
}

struct WavHeader convertHeader(struct WavHeaderInBytes headerInBytes) {
    struct WavHeader wavHeader;

    wavHeader.chunkSizeInt = convert4(headerInBytes.chunkSize);
    wavHeader.subChunk1SizeInt = convert4(headerInBytes.subChunk1Size);
    wavHeader.audioFormatInt = convert2(headerInBytes.audioFormat);
    wavHeader.numChannelsInt = convert2(headerInBytes.numChannels);
    wavHeader.sampleRateInt = convert4(headerInBytes.sampleRate);
    wavHeader.byteRateInt = convert4(headerInBytes.byteRate);
    wavHeader.blockAlignInt = convert2(headerInBytes.blockAlign);
    wavHeader.bitsPerSampleInt = convert2(headerInBytes.bitsPerSample);
    wavHeader.subChunk2SizeInt = convert4(headerInBytes.subChunk2Size);

    return wavHeader;
}

void proceedHeader(uint8_t *header, long headerLength) {
    for (int i = 0; i < headerLength; i++)
    {
        printf("%c ", header[i]);
    }

    struct WavHeaderInBytes headerInBytes;

    for (int i = 0; i < 4; i++)
    {
        headerInBytes.chunkSize[i] = header[i + 4];
        headerInBytes.subChunk1Size[i] = header[i + 16];
        headerInBytes.sampleRate[i] = header[i + 24];
        headerInBytes.byteRate[i] = header[i + 28];
        headerInBytes.subChunk2Size[i] = header[i + 40];
    }

    for (int i = 0; i < 2; i++)
    {
        headerInBytes.audioFormat[i] = header[i + 20];
        headerInBytes.numChannels[i] = header[i + 22];
        headerInBytes.blockAlign[i] = header[i + 32];
        headerInBytes.bitsPerSample[i] = header[i + 34];
    }

    struct WavHeader wavHeader = convertHeader(headerInBytes);

    printf("\nChunk size: %u\nsubChunk 1 Size: %u\naudio Format: %u\nnum channels: %u"
           "\nsample rate: %u\nbyte rate: %u\nblock align: %u\nbits per sample: %u\nsubChunk 2 size: %u\n",
           wavHeader.chunkSizeInt,
           wavHeader.subChunk1SizeInt,
           wavHeader.audioFormatInt,
           wavHeader.numChannelsInt,
           wavHeader.sampleRateInt,
           wavHeader.byteRateInt,
           wavHeader.blockAlignInt,
           wavHeader.bitsPerSampleInt,
           wavHeader.subChunk2SizeInt);
}

short proceedFile() {
    int input, output, openFlags;
    mode_t filePerms;
    long header;
    uint8_t buffer[BUF_SIZE];
    openFlags = O_CREAT | O_WRONLY | O_TRUNC;
    filePerms = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH;
    input = open("../Master Of Puppets.wav", O_RDONLY);
    output = open("output.wav", openFlags, filePerms);
    if (input == -1)
    {
        printf("input open error");
        return -1;
    }
    if (output == -1)
    {
        printf("output open error");
    }
    printf("open result = %d\n", input);

    header = read(input, buffer, BUF_SIZE);
    if (header > 0)
    {
        printf("reading succeeded\n");
        proceedHeader(buffer, header);

        write(output, buffer, BUF_SIZE);

        int16_t sample;
        while(read(input, &sample, sizeof sample)) {
            int64_t louderSample = sample * 2;
            if (louderSample > INT16_MAX) {
                louderSample = INT16_MAX;
            } else if (louderSample < INT16_MIN) {
                louderSample = INT16_MIN;
            }
            sample = (int16_t) louderSample;
            write(output, &sample, sizeof(sample));
        }

        if (close(input) == -1)
        {
            printf("input close error");
            return -1;
        }
        if (close(output) == -1)
        {
            printf("output close error");
            return -1;
        }
    }
    else
    {
        printf("reading error");
        return -1;
    }

    return 0;
}
