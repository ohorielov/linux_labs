#ifndef LAB1_H
#define LAB1_H
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#define HEADER_SIZE 44


typedef struct header_struct {
    union {
        char chunk_id_s[4];
        uint32_t chunk_id;
    } id_descr;
    uint32_t chunk_size;
    union {
        char format_s[4];
        uint32_t format;
    } format_descr;

    union {
        char subchunk1_id_s[4];
        uint32_t subchunk1_id;
    } subchunk1_descr;
    uint32_t subchunk1_size;
    union {
        char audio_format_s[2];
        uint16_t audio_format;
    } audio_format_descr;
    uint16_t num_channels;
    uint32_t sample_rate;
    uint32_t byte_rate;
    uint16_t block_align;
    uint16_t bits_per_sample;

    union {
        char subchunk2_id_s[4];
        uint32_t subchunk2_id;
    } subchunk2_descr;
    uint32_t subchunk2_size;

} wav_header;

union header_data {
    char data[HEADER_SIZE];
    wav_header header;
};

#endif
