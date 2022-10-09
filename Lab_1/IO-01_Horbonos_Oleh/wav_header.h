#ifndef WAV_HEADER_H
#define WAV_HEADER_H

#include <stdint.h>

typedef struct 
{
    uint8_t riff[4];
    uint32_t chunkSize;
    uint8_t wave[4];
} riff_struct;

typedef struct 
{
    uint8_t fmt_marker[4];
    uint32_t subchunkSize;
    uint16_t audioFormat;
    uint16_t numChanels;
    uint32_t sampleRate;
    uint32_t byteRate;
    uint16_t blockAlign;
    uint16_t bitsPerSample;
} format_struct;

typedef struct
{
    uint8_t data_marker[4];
    uint32_t dataSize;
} data_struct;

typedef struct 
{
    riff_struct riff;
    format_struct fmt;
    data_struct data;
} wav_header;

#endif