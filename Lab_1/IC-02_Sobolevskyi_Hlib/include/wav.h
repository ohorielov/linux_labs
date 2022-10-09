#pragma once

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

#define RIFF_SIZE 12
#define FMT_CHANK_SIZE 24

#define DATA_CHANK_SIZE 8

#define WAV_METADATA_SIZE (RIFF_SIZE + FMT_CHANK_SIZE + DATA_CHANK_SIZE)

// const char format[] = "WAVE";

typedef struct
{
    uint32_t id;
    uint32_t chuck_size;
    uint32_t format;
} RIFF;

typedef struct 
{
    uint32_t id;
    uint32_t size;
    uint16_t format;
    uint16_t num_channels;
    uint32_t sample_rate;
    uint32_t byte_rate;
    uint16_t block_align;
    uint16_t bits_per_sample;
} fmt_subchunk;

typedef struct
{
    uint32_t id;
    uint32_t size;
    uint8_t *data;
} data_subchunk;

typedef struct
{
    RIFF riff;
    fmt_subchunk fmt_subchunk;
    data_subchunk data_subchunk;
} WAV;

WAV* load_wav(const char* filename);

void update_wav(WAV* wav);

void save_wav(WAV* wav, const char* filename);