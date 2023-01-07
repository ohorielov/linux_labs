#include "stdlib.h"
#include "stdio.h"
#include "stdint.h"
#include "string.h"
#include "wav_processing.h"

#define ELEMENTS_TO_READ_1 1
#define ELEMENTS_TO_READ_4 4
#define BYTES_1 1
#define BYTES_2 2
#define BYTES_4 4

void read_wav_file(const char *filename, struct Wav_header *wav) {
    FILE *file = fopen(filename, "rb");

    if (file == NULL) {
        printf("File %s is failed to open", filename);
        exit(-1);
    }

    fread(&wav->chunk_id, BYTES_1, ELEMENTS_TO_READ_4, file);
    if (strncmp("RIFF", wav->chunk_id, sizeof wav->chunk_id)) {
        printf("File %s isn't in RIFF (WAV container) format\n", filename);
        exit(-1);
    }
    printf("ChunkID: %s\n", wav->chunk_id);

    fread(&wav->chunk_size, BYTES_4, ELEMENTS_TO_READ_1, file);
    printf("ChunkSize: %u\n", wav->chunk_size);

    fread(&wav->format, BYTES_1, ELEMENTS_TO_READ_4, file);
    if (strncmp("WAVE", wav->format, sizeof wav->format)) {
        printf("File %s isn't in WAVE format\n", filename);
        exit(-1);
    }
    printf("Format: %s\n", wav->format);

    fread(&wav->subchunk1_id, BYTES_1, ELEMENTS_TO_READ_4, file);
    printf("Subchunk1 ID: %s\n", wav->subchunk1_id);

    fread(&wav->subchunk1_size, BYTES_4, ELEMENTS_TO_READ_1, file);
    printf("Subchunk1 Size: %u\n", wav->subchunk1_size);

    fread(&wav->audio_format, BYTES_2, ELEMENTS_TO_READ_1, file);
    printf("Audio format: %hu\n", wav->audio_format);

    fread(&wav->num_channels, BYTES_2, ELEMENTS_TO_READ_1, file);
    printf("Num channels: %hu\n", wav->num_channels);

    fread(&wav->sample_rate, BYTES_4, ELEMENTS_TO_READ_1, file);
    printf("Sample rate: %u\n", wav->sample_rate);

    fread(&wav->byte_rate, BYTES_4, ELEMENTS_TO_READ_1, file);
    printf("Byte rate: %u\n", wav->byte_rate);

    fread(&wav->block_align, BYTES_2, ELEMENTS_TO_READ_1, file);
    printf("Block align: %hu\n", wav->block_align);

    fread(&wav->bits_per_sample, BYTES_2, ELEMENTS_TO_READ_1, file);
    printf("Bits per sample: %hu\n", wav->bits_per_sample);

    fread(&wav->subchunk2_id, BYTES_1, ELEMENTS_TO_READ_4, file);
    printf("Subchunk2 ID: %s\n", wav->subchunk2_id);

    fread(&wav->subchunk2_size, BYTES_4, ELEMENTS_TO_READ_1, file);
    printf("Subchunk2 Size: %u\n", wav->subchunk2_size);

    wav->data = malloc(wav->subchunk2_size);
    fread(wav->data, wav->subchunk2_size, ELEMENTS_TO_READ_1, file);

    fclose(file);
}

void edit_volume(float scale, struct Wav_header *wav) {
    for (int i = 0; i < wav->subchunk2_size / sizeof(int16_t); i++) {
        int16_t sample = *(wav->data + i);
        sample = (int16_t)(sample * scale);
        wav->data[i] = sample;
    }
}


void write_wav_file(const char *filename, struct Wav_header *wav) {
    FILE *file = fopen(filename, "wb");
    
    fwrite(&wav->chunk_id, BYTES_1, ELEMENTS_TO_READ_4, file);
    fwrite(&wav->chunk_size, BYTES_4, ELEMENTS_TO_READ_1, file);
    fwrite(&wav->format, BYTES_1, ELEMENTS_TO_READ_4, file);
    fwrite(&wav->subchunk1_id, BYTES_1, ELEMENTS_TO_READ_4, file);
    fwrite(&wav->subchunk1_size, BYTES_4, ELEMENTS_TO_READ_1, file);
    fwrite(&wav->audio_format, BYTES_2, ELEMENTS_TO_READ_1, file);
    fwrite(&wav->num_channels, BYTES_2, ELEMENTS_TO_READ_1, file);
    fwrite(&wav->sample_rate, BYTES_4, ELEMENTS_TO_READ_1, file);
    fwrite(&wav->byte_rate, BYTES_4, ELEMENTS_TO_READ_1, file);
    fwrite(&wav->block_align, BYTES_2, ELEMENTS_TO_READ_1, file);
    fwrite(&wav->bits_per_sample, BYTES_2, ELEMENTS_TO_READ_1, file);
    fwrite(&wav->subchunk2_id, BYTES_1, ELEMENTS_TO_READ_4, file);
    fwrite(&wav->subchunk2_size, BYTES_4, ELEMENTS_TO_READ_1, file);
    fwrite(wav->data, wav->subchunk2_size, ELEMENTS_TO_READ_1, file);

    fclose(file);
}

