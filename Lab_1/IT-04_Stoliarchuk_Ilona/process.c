#include "stdlib.h"
#include "stdio.h"
#include "stdint.h"
#include "process.h"


int read(const char *filename, struct WavHeader *wav){
	FILE *input_data = fopen(filename, "rb");
	if (input_data == NULL){
		printf("Failed to open");
		return 0;
	}
	fread(&wav->chunkID, 4, 1, input_data);
	fread(&wav->chunkSize, 4, 1, input_data);
	fread(&wav->format, 4, 1, input_data);
	fread(&wav->subchunk1ID, 4, 1, input_data);
	fread(&wav->subchunk1Size, 4, 1, input_data);
	fread(&wav->audioFormat, 2, 1, input_data);
	fread(&wav->numChannels, 2, 1, input_data);
	fread(&wav->sampleRate, 4, 1, input_data);
	fread(&wav->byteRate, 4, 1, input_data);
	fread(&wav->blockAlign, 2, 1, input_data);
	fread(&wav->bitsPerSample, 2, 1, input_data);
	fread(&wav->subchunk2ID, 4, 1, input_data);
	fread(&wav->subchunk2Size, 4, 1, input_data);
	wav->data = malloc(wav->subchunk2Size);
	fread(wav->data, wav->subchunk2Size, 1, input_data);
	fclose(input_data);
	return 0;
}

void edit(float a, struct WavHeader *wav){
	uint32_t samplesCount = wav->subchunk2Size / sizeof(int16_t);
	for(int i = 0; i < samplesCount; i++) {
		int16_t sample = wav->data[i];
		sample = sample * a;
		wav->data[i] = sample;
	}
}

void print(const char *filename, struct WavHeader *wav){
    printf("ChunkID: %s\n", wav->chunkID);
    printf("ChunkSize: %u\n", wav->chunkSize);
    printf("Format: %s\n", wav->format);
    printf("Subchunk1ID: %s\n", wav->subchunk1ID);
    printf("Subchunk1Size: %u\n", wav->subchunk1Size);
    printf("AudioFormat: %hu\n", wav->audioFormat);
    printf("NumChannel: %hu\n", wav->numChannels);
    printf("SampleRate: %u\n", wav->sampleRate);
    printf("ByteRate: %u\n", wav->byteRate);
    printf("BlockAlign: %hu\n", wav->blockAlign);
    printf("BitsPerSample: %hu\n", wav->bitsPerSample);
    printf("Subchunk2ID: %s\n", wav->subchunk2ID);
    printf("Subchunk2Size: %u\n", wav->subchunk2Size);

}	

int write(const char *filename, struct WavHeader *wav){
	FILE *output_data = fopen(filename, "wb");
	if (output_data == NULL){
		printf("Failed to create");
		return 0;
	}
	fwrite(&wav->chunkID, 4, 1, output_data);
	fwrite(&wav->chunkSize, 4, 1, output_data);
	fwrite(&wav->format, 4, 1, output_data);
	fwrite(&wav->subchunk1ID, 4, 1, output_data);
	fwrite(&wav->subchunk1Size, 4, 1, output_data);
	fwrite(&wav->audioFormat, 2, 1, output_data);
	fwrite(&wav->numChannels, 2, 1, output_data);
	fwrite(&wav->sampleRate, 4, 1, output_data);
	fwrite(&wav->byteRate, 4, 1, output_data);
	fwrite(&wav->blockAlign, 2, 1, output_data);
	fwrite(&wav->bitsPerSample, 2, 1, output_data);
	fwrite(&wav->subchunk2ID, 4, 1, output_data);
	fwrite(&wav->subchunk2Size, 4, 1, output_data);
	fwrite(wav->data, wav->subchunk2Size, 1, output_data);
	fclose(output_data);
	return 0;
}

