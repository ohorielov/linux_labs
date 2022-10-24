#include "stdlib.h"
#include "stdio.h"
#include "stdint.h"
#include "wav_header.h"
#include "wav_processor.h"

void load_wav(const char *filename, wav_header *wav) {
	FILE *file = fopen(filename, "rb");

	fread(&wav->chunk_id, 4, 1, file);
	fread(&wav->chunk_size, 4, 1, file);
	fread(&wav->format, 4, 1, file);

	fread(&wav->subchunk1_id, 4, 1, file);
	fread(&wav->subchunk1_size, 4, 1, file);
	fread(&wav->audio_format, 2, 1, file);
	fread(&wav->num_channels, 2, 1, file);
	fread(&wav->sample_rate, 4, 1, file);
	fread(&wav->byte_rate, 4, 1, file);
	fread(&wav->block_align, 2, 1, file);
	fread(&wav->bits_per_sample, 2, 1, file);

	fread(&wav->subchunk2_id, 4, 1, file);
	fread(&wav->subchunk2_size, 4, 1, file);

	wav->data = malloc(wav->subchunk2_size);
	fread(wav->data, wav->subchunk2_size, 1, file);

	fclose(file);
}

void write_wav(const char *filename, wav_header *wav) {
	FILE* file = fopen(filename, "wb");

	fwrite(&wav->chunk_id, 4, 1, file);
	fwrite(&wav->chunk_size, 4, 1, file);
	fwrite(&wav->format, 4, 1, file);

	fwrite(&wav->subchunk1_id, 4, 1, file);
	fwrite(&wav->subchunk1_size, 4, 1, file);
	fwrite(&wav->audio_format, 2, 1, file);
	fwrite(&wav->num_channels, 2, 1, file);
	fwrite(&wav->sample_rate, 4, 1, file);
	fwrite(&wav->byte_rate, 4, 1, file);
	fwrite(&wav->block_align, 2, 1, file);
	fwrite(&wav->bits_per_sample, 2, 1, file);

	fwrite(&wav->subchunk2_id, 4, 1, file);
	fwrite(&wav->subchunk2_size, 4, 1, file);

	fwrite(wav->data, wav->subchunk2_size, 1, file);

	fclose(file);
}

void dump_wav(wav_header *wav) {
	printf("Chunk ID: %c%c%c%c\n", wav->chunk_id & 0xFF, (wav->chunk_id >> 8) & 0xFF, (wav->chunk_id >> 16) & 0xFF, (wav->chunk_id >> 24) & 0xFF);
	printf("Chunk size: %u\n", wav->chunk_size);
	printf("Format: %c%c%c%c\n", wav->format & 0xFF, (wav->format >> 8) & 0xFF, (wav->format >> 16) & 0xFF, (wav->format >> 24) & 0xFF);

	printf("Subchunk 1 ID: %c%c%c%c\n", wav->subchunk1_id & 0xFF, (wav->subchunk1_id >> 8) & 0xFF, (wav->subchunk1_id >> 16) & 0xFF, (wav->subchunk1_id >> 24) & 0xFF);
	printf("Subchunk 1 size: %u\n", wav->subchunk1_size);
	printf("Audio format: %hu\n", wav->audio_format);
	printf("Num channels: %hu\n", wav->num_channels);
	printf("Sample rate: %u\n", wav->sample_rate);
	printf("Byte rate: %u\n", wav->byte_rate);
	printf("Block align: %hu\n", wav->block_align);
	printf("Bits per sample: %hu\n", wav->bits_per_sample);

	printf("Subchunk 2 ID: %c%c%c%c\n", wav->subchunk2_id & 0xFF, (wav->subchunk2_id >> 8) & 0xFF, (wav->subchunk2_id >> 16) & 0xFF, (wav->subchunk2_id >> 24) & 0xFF);
	printf("Subchunk 2 size: %u\n", wav->subchunk2_size);
}

void adjust_wav(wav_header *wav, float scale) {
	int samples_count = wav->subchunk2_size / sizeof(int16_t);

	for(int i = 0; i < samples_count; i++) {
		int16_t sample = wav->data[i];
		sample += (int16_t)(sample * scale);
		wav->data[i] = sample;
	}
}
