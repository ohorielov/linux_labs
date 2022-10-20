#ifndef WAV_HANDLE
#define WAV_HANDLE

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#define INT_FIELD_PRINT(msg, fld) printf("%s %d\n", msg, fld)
#define CHAR_FIELD_PRINT(msg, fld) printf("%s %c%c%c%c\n", msg, fld[0], fld[1], fld[2], fld[3])

struct wavRiff {
    uint8_t chunkId[4];
    uint32_t chunkSize;
    uint8_t format[4];
};

struct wavFmt {
    uint8_t subchunk1Id[4];
    uint32_t subchunk1Size;
    uint16_t audioFormat;
    uint16_t numChannels;
    uint32_t sampleRate;
    uint32_t byteRate;
    uint16_t blockAlign;
    uint16_t bitsPerSample;
};

struct wavDataHeader {
    uint8_t subchunk2Id[4];
    uint32_t subchunk2Size;
    int8_t *wavData;
};

struct wav {
    struct wavRiff riff;
    struct wavFmt fmt;
    struct wavDataHeader dataHeader;
};

struct wav* wav_file_open(const uint8_t* fileName); 

void wav_change_volume(struct wav* someWav, int8_t changeValue, bool isIncrease);

void wav_file_create(struct wav* someWav, const uint8_t* fileName); 

void wav_print_header(struct wav* someWav);

#endif