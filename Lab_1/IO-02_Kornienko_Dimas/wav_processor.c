#include "stdlib.h"
#include "stdio.h"
#include "stdint.h"
#include "wav_processor.h"

//зчитуємо subchunk2_size у data іншу менш важливу інфу у header
void load_wav(const char *filename, wav_header *wav, int16_t **data) {
	FILE *file = fopen(filename, "rb");

	fread(wav, sizeof(wav_header), 1, file);

	*data = malloc(wav->subchunk2_size);
	fread(*data, wav->subchunk2_size, 1, file);

	fclose(file);
}
//записуємо файл, спочатку header, потім data
void write_wav(const char *filename, wav_header *wav, int16_t *data) {
	FILE* file = fopen(filename, "wb");

	fwrite(wav, sizeof(wav_header), 1, file);
	fwrite(data, wav->subchunk2_size, 1, file);

	fclose(file);
}
//Вивести повну інформацію про файл
void structure_wav(wav_header *wav) {
	printf("Chunk ID: %c%c%c%c\n",
			wav->chunk_id & 0xFF,
			(wav->chunk_id >> 8) & 0xFF,
			(wav->chunk_id >> 16) & 0xFF,
			(wav->chunk_id >> 24) & 0xFF);

	printf("Chunk size: %u\n", wav->chunk_size);
	printf("Format: %c%c%c%c\n",
			wav->format & 0xFF,
			(wav->format >> 8) & 0xFF,
			(wav->format >> 16) & 0xFF,
			(wav->format >> 24) & 0xFF);

	printf("Subchunk 1 ID: %c%c%c%c\n",
			wav->subchunk1_id & 0xFF,
			(wav->subchunk1_id >> 8) & 0xFF,
			(wav->subchunk1_id >> 16) & 0xFF,
			(wav->subchunk1_id >> 24) & 0xFF);

	printf("Subchunk 1 size: %u\n", wav->subchunk1_size);
	printf("Audio format: %hu\n", wav->audio_format);
	printf("Num channels: %hu\n", wav->num_channels);
	printf("Sample rate: %u\n", wav->sample_rate);
	printf("Byte rate: %u\n", wav->byte_rate);
	printf("Block align: %hu\n", wav->block_align);
	printf("Bits per sample: %hu\n", wav->bits_per_sample);

	printf("Subchunk 2 ID: %c%c%c%c\n",
			wav->subchunk2_id & 0xFF,
			(wav->subchunk2_id >> 8) & 0xFF,
			(wav->subchunk2_id >> 16) & 0xFF,
			(wav->subchunk2_id >> 24) & 0xFF);

	printf("Subchunk 2 size: %u\n", wav->subchunk2_size);
}
//За допомогою цієї функції ми можемо редагувати гучність. Переписуючи зміну data
void adjust_wav(wav_header *wav, int16_t *data, float scale) {
	uint32_t samples_count = wav->subchunk2_size / sizeof(int16_t);

	uint32_t i;

	for(i = 0; i < samples_count; i++) {
		int16_t sample = data[i];
		sample += sample * scale;
		data[i] = sample;
	}
}
