#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
typedef struct
{
uint32_t riff;
uint32_t file_size;

uint64_t wave_fmt;
uint32_t header_rest;
uint16_t compression;
uint16_t ch_number;
uint32_t discret_freq;
uint32_t bpsec;
uint16_t bpsam;
uint16_t bpsam_channel;

uint32_t data_id;
uint32_t data_size;
}wav_header;

typedef struct
{
uint32_t chunkID;
uint32_t chunkSize;
void* data;
}sub_chunk;

void say(const char*);
wav_header* read_wav(const char*);
