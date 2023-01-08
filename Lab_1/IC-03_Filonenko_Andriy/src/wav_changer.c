#include "wav_changer.h"

#define BYTES4 4
#define BYTES2 2
#define NUMBER_OF_ELEMENTS 1

void read_wav(FILE* file, struct WavHeader* wav_h) {

    fread(&wav_h->riff.chunk_id, BYTES4, NUMBER_OF_ELEMENTS, file);
	fread(&wav_h->riff.chunk_size, BYTES4, NUMBER_OF_ELEMENTS, file);
	fread(&wav_h->riff.format, BYTES4, NUMBER_OF_ELEMENTS, file);

	fread(&wav_h->fmt.subchunk1_id, BYTES4, NUMBER_OF_ELEMENTS, file);
	fread(&wav_h->fmt.subchunk1_size, BYTES4, NUMBER_OF_ELEMENTS, file);
	fread(&wav_h->fmt.audio_format, BYTES2, NUMBER_OF_ELEMENTS, file);
	fread(&wav_h->fmt.num_channels, BYTES2, NUMBER_OF_ELEMENTS, file);
	fread(&wav_h->fmt.sample_rate, BYTES4, NUMBER_OF_ELEMENTS, file);
	fread(&wav_h->fmt.byte_rate, BYTES4, NUMBER_OF_ELEMENTS, file);
	fread(&wav_h->fmt.block_align, BYTES2, NUMBER_OF_ELEMENTS, file);
	fread(&wav_h->fmt.bits_per_sample, BYTES2, NUMBER_OF_ELEMENTS, file);

	fread(&wav_h->data.subchunk2_id, BYTES4, NUMBER_OF_ELEMENTS, file);
	fread(&wav_h->data.subchunk2_size, BYTES4, NUMBER_OF_ELEMENTS, file);
	wav_h->data.data = malloc(wav_h->data.subchunk2_size);
    fread(wav_h->data.data, wav_h->data.subchunk2_size, NUMBER_OF_ELEMENTS, file);

    fclose(file);
}

void write_wav(FILE* file, struct WavHeader *wav_h) {
	fwrite(&wav_h->riff.chunk_id, BYTES4, NUMBER_OF_ELEMENTS, file);
	fwrite(&wav_h->riff.chunk_size, BYTES4, NUMBER_OF_ELEMENTS, file);
	fwrite(&wav_h->riff.format, BYTES4, NUMBER_OF_ELEMENTS, file);

	fwrite(&wav_h->fmt.subchunk1_id, BYTES4, NUMBER_OF_ELEMENTS, file);
	fwrite(&wav_h->fmt.subchunk1_size, BYTES4, NUMBER_OF_ELEMENTS, file);
	fwrite(&wav_h->fmt.audio_format, BYTES2, NUMBER_OF_ELEMENTS, file);
	fwrite(&wav_h->fmt.num_channels, BYTES2, NUMBER_OF_ELEMENTS, file);
	fwrite(&wav_h->fmt.sample_rate, BYTES4, NUMBER_OF_ELEMENTS, file);
	fwrite(&wav_h->fmt.byte_rate, BYTES4, NUMBER_OF_ELEMENTS, file);
	fwrite(&wav_h->fmt.block_align, BYTES2, NUMBER_OF_ELEMENTS, file);
	fwrite(&wav_h->fmt.bits_per_sample, BYTES2, NUMBER_OF_ELEMENTS, file);

	fwrite(&wav_h->data.subchunk2_id, BYTES4, NUMBER_OF_ELEMENTS, file);
	fwrite(&wav_h->data.subchunk2_size, BYTES4, NUMBER_OF_ELEMENTS, file);
	fwrite(wav_h->data.data, wav_h->data.subchunk2_size, NUMBER_OF_ELEMENTS, file);

	fclose(file);
}

void print(struct WavHeader *wav_h) {
    printf("Riff: %s\n", wav_h->riff.chunk_id);
	printf("Size: %d\n", wav_h->riff.chunk_size);
	printf("Format: %s\n", wav_h->riff.format);
	printf("Subchunk 1 id: %s\n", wav_h->fmt.subchunk1_id);
	printf("Subchunk 1 size: %d\n", wav_h->fmt.subchunk1_size);
	printf("Audio format: %d\n", wav_h->fmt.audio_format);
	printf("Num channels: %d\n", wav_h->fmt.num_channels);
	printf("Sample rate: %d\n", wav_h->fmt.sample_rate);
	printf("Byte rate: %d\n", wav_h->fmt.byte_rate);
	printf("Block align: %d\n", wav_h->fmt.block_align);
	printf("Bits per sample: %d\n", wav_h->fmt.bits_per_sample);
	printf("Subchunk 2 ID: %s\n", wav_h->data.subchunk2_id);
	printf("Subchunk 2 size: %d\n", wav_h->data.subchunk2_size);
}

void change_volume(struct WavHeader *wav_h, float scale) {
	for (int i = 0; i < wav_h->data.subchunk2_size / sizeof(short); i++){
    	wav_h->data.data[i] = (short) (wav_h->data.data[i] * scale);
	}
}
