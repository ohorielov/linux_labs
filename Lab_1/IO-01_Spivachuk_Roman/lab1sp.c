#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "lab1sp.h"

struct header_struct {
    char chunk_id[4];
    uint32_t chunk_size;
    char format[4];

    char subchunk1_id[4];
    uint32_t subchunk1_size;
    uint16_t audio_format;
    uint16_t num_channels;
    uint32_t sample_rate;
    uint32_t byte_rate;
    uint16_t block_align;
    uint16_t bits_per_sample;

    char subchunk2_id[4];
    uint32_t subchunk2_size;
};

union header_data {
    char data[HEADER_SIZE];
    wav_header header;
};

union header_data *file_header;


FILE* read_wav_file(char* fileName) {
    FILE* wav_ptr;
    wav_ptr = fopen(fileName, "r");

    if (!wav_ptr) {
        fprintf(stderr, "%s can't be opened\n", fileName);
        exit(1);
    }

    file_header = (union header_data *) malloc(HEADER_SIZE);
    for (int i = 0; i < HEADER_SIZE && (file_header->data[i] = getc(wav_ptr)) != EOF; i++);

    printf("ChunkID: %.4s\n", file_header->header.chunk_id);
    printf("Chunk size: %u\n", file_header->header.chunk_size);
    printf("Format: %.4s\n", file_header->header.format);

    printf("Subchunk 1 ID: %s\n", file_header->header.subchunk1_id);
    printf("Subchunk 1 size: %u\n", file_header->header.subchunk1_size);
    printf("Audio format: %u\n", file_header->header.audio_format);
    printf("Number of channels: %us\n", file_header->header.num_channels);
    printf("Sample rate: %u\n", file_header->header.sample_rate);
    printf("Byte rate: %u\n", file_header->header.byte_rate);
    printf("Block align: %us\n", file_header->header.block_align);
    printf("Bits per sample: %us\n", file_header->header.bits_per_sample);

    printf("Subchunk 2 ID: %.4s\n", file_header->header.subchunk2_id);
    printf("Subchunk 2 size: %u\n", file_header->header.subchunk2_size);

    printf("\nChanging volume of wav file\n");

    return wav_ptr;
}

FILE* write_edited_data(char* fileName, FILE* dataSource, float changeValue) {
    FILE* edited_wav;
    edited_wav = fopen(fileName, "w");

    if (!edited_wav) {
        fprintf(stderr, "%s can't be opened\n", fileName);
        exit(1);
    }

    for (int i = 0; i < HEADER_SIZE; i++) {
        putc( file_header->data[i], edited_wav);
    }

    // writing edited data to new file
    uint16_t buffer;
    while (fread(&buffer, 2, 1, dataSource)) {
        buffer = buffer * (float)changeValue;
        fwrite(&buffer, 2, 1, edited_wav);
    }

    return edited_wav;
}