#include "wav_edit.h"

#define in_file "../Master Of Puppets.wav"
#define res_file "../Master Of Puppets(edited).wav"

void read_wav(FILE* file, struct WavHeader* wav_h) {

    fread(&wav_h->riff.chunk_id, 4, 1, file);
	fread(&wav_h->riff.chunk_size, 4, 1, file);
	fread(&wav_h->riff.format, 4, 1, file);

	fread(&wav_h->fmt.subchunk1_id, 4, 1, file);
	fread(&wav_h->fmt.subchunk1_size, 4, 1, file);
	fread(&wav_h->fmt.audio_format, 2, 1, file);
	fread(&wav_h->fmt.num_channels, 2, 1, file);
	fread(&wav_h->fmt.sample_rate, 4, 1, file);
	fread(&wav_h->fmt.byte_rate, 4, 1, file);
	fread(&wav_h->fmt.block_align, 2, 1, file);
	fread(&wav_h->fmt.bits_per_sample, 2, 1, file);

	fread(&wav_h->data.subchunk2_id, 4, 1, file);
	fread(&wav_h->data.subchunk2_size, 4, 1, file);
	wav_h->data.data = malloc(wav_h->data.subchunk2_size);
    fread(wav_h->data.data, wav_h->data.subchunk2_size, 1, file);

    fclose(file);
}

void write_wav(FILE* file, struct WavHeader *wav_h) {

FILE *file_input = fopen(in_file, "rb")
if(input == NULL){
printf("File not found");
return 0;
}


	fwrite(&wav_h->riff.chunk_id, 4, 1, file);
	fwrite(&wav_h->riff.chunk_size, 4, 1, file);
	fwrite(&wav_h->riff.format, 4, 1, file);

	fwrite(&wav_h->fmt.subchunk1_id, 4, 1, file);
	fwrite(&wav_h->fmt.subchunk1_size, 4, 1, file);
	fwrite(&wav_h->fmt.audio_format, 2, 1, file);
	fwrite(&wav_h->fmt.num_channels, 2, 1, file);
	fwrite(&wav_h->fmt.sample_rate, 4, 1, file);
	fwrite(&wav_h->fmt.byte_rate, 4, 1, file);
	fwrite(&wav_h->fmt.block_align, 2, 1, file);
	fwrite(&wav_h->fmt.bits_per_sample, 2, 1, file);

	fwrite(&wav_h->data.subchunk2_id, 4, 1, file);
	fwrite(&wav_h->data.subchunk2_size, 4, 1, file);
	fwrite(wav_h->data.data, wav_h->data.subchunk2_size, 1, file);

	fclose(file);
}

int wav_output(struct WavHeader *wav_h){
FILE *out_data=fopen(res_file, "wb");

if (out_data == NULL){
printf("FILE WASN`T CREATED");
return 0;
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