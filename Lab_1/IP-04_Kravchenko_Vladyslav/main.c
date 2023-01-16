#include <errno.h>
extern int errno;

#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>


#define INPUT_LOCATION "..//Master Of Puppets.wav"
#define OUTPUT_LOCATION "./out.wav"
#define struct_wav_size 52


struct Wav
{
	struct
	{
		uint8_t chunkID[4];
		uint32_t chunkSize;
		uint8_t format[4];
		uint8_t subchunk1ID[4];
		uint32_t subchunk1Size;
		uint16_t audioFormat;
		uint16_t numChannels;
		uint32_t sampleRate;
		uint32_t byteRate;
		uint16_t blockAlign;
		uint16_t bitsPerSample;
		uint8_t subchunk2ID[4];
		uint32_t subchunk2Size;
	} header;
	uint16_t* data;
};


struct Wav* read_wav(const char* input_wav_name)
{
	if (access(input_wav_name, F_OK) != 0)
	{
		perror("error occured in read_wav function");
		return NULL;
	}

	FILE *raw_input = fopen(input_wav_name, "rb");

	struct Wav* result_wav_pointer = (struct Wav*)malloc(struct_wav_size);

	fread(&result_wav_pointer->header.chunkID,			4,	1, raw_input);
	fread(&result_wav_pointer->header.chunkSize,		4,	1, raw_input);
	fread(&result_wav_pointer->header.format,			4,	1, raw_input);
	fread(&result_wav_pointer->header.subchunk1ID,		4,	1, raw_input);
	fread(&result_wav_pointer->header.subchunk1Size,	4,	1, raw_input);
	fread(&result_wav_pointer->header.audioFormat,		2,	1, raw_input);
	fread(&result_wav_pointer->header.numChannels,		2,	1, raw_input);
	fread(&result_wav_pointer->header.sampleRate,		4,	1, raw_input);
	fread(&result_wav_pointer->header.byteRate,			4,	1, raw_input);
	fread(&result_wav_pointer->header.blockAlign,		2,	1, raw_input);
	fread(&result_wav_pointer->header.bitsPerSample,	2,	1, raw_input);
	fread(&result_wav_pointer->header.subchunk2ID,		4,	1, raw_input);
	fread(&result_wav_pointer->header.subchunk2Size,	4,	1, raw_input);
	result_wav_pointer->data =
		(uint16_t*)malloc(result_wav_pointer->header.subchunk2Size);
	fread(
		result_wav_pointer->data,
		result_wav_pointer->header.subchunk2Size,
		1,
		raw_input
	);
	
	fclose(raw_input);
	return result_wav_pointer;
}

void adjust_volume(struct Wav* wav_pointer, double decibels)
{
	double lin_difference = pow(10, decibels/10);  //m=10^(n/10), n-db
	int data_size = wav_pointer->header.subchunk2Size/sizeof(uint16_t);
	for (uint32_t i = 0; i < data_size; i++)
		wav_pointer->data[i] *= lin_difference;
}

void write_wav(struct Wav* wav_pointer, const char* filename)
{
	FILE *out_data = fopen(filename, "wb");

	if (out_data == NULL)
	{
		perror("error occured in write_wav function");
		return;
	}

	fwrite(&wav_pointer->header.chunkID,		4,	1, out_data);
	fwrite(&wav_pointer->header.chunkSize,		4,	1, out_data);
	fwrite(&wav_pointer->header.format,			4,	1, out_data);
	fwrite(&wav_pointer->header.subchunk1ID,	4,	1, out_data);
	fwrite(&wav_pointer->header.subchunk1Size,	4,	1, out_data);
	fwrite(&wav_pointer->header.audioFormat,	2,	1, out_data);
	fwrite(&wav_pointer->header.numChannels,	2,	1, out_data);
	fwrite(&wav_pointer->header.sampleRate,		4,	1, out_data);
	fwrite(&wav_pointer->header.byteRate,		4,	1, out_data);
	fwrite(&wav_pointer->header.blockAlign,		2,	1, out_data);
	fwrite(&wav_pointer->header.bitsPerSample,	2,	1, out_data);
	fwrite(&wav_pointer->header.subchunk2ID,	4,	1, out_data);
	fwrite(&wav_pointer->header.subchunk2Size,	4,	1, out_data);
	fwrite(wav_pointer->data, wav_pointer->header.subchunk2Size, 1, out_data);

	fclose(out_data);
}

// only used for debugging, isnt a necessary part of a program
// void print_header(struct Wav* wav_pointer)
// {
// 	if (wav_pointer == NULL) return;

// 	printf("Header info\n");
// 	printf("%s\t\t%.4s \n",	"ChunkID",		wav_pointer->header.chunkID);
// 	printf("%s\t%u \n",		"ChunkSize",	wav_pointer->header.chunkSize);
// 	printf("%s\t\t%.4s \n",	"Format",		wav_pointer->header.format);
// 	printf("%s\t%.4s \n",	"Subchunk1ID",	wav_pointer->header.subchunk1ID);
// 	printf("%s\t%u \n",		"Subchunk1Size",wav_pointer->header.subchunk1Size);
// 	printf("%s\t%u \n",		"AudioFormat",	wav_pointer->header.audioFormat);
// 	printf("%s\t%u \n",		"NumChannels",	wav_pointer->header.numChannels);
// 	printf("%s\t%u \n",		"SampleRate",	wav_pointer->header.sampleRate);
// 	printf("%s\t%u \n",		"ByteRate",		wav_pointer->header.byteRate);
// 	printf("%s\t%u \n",		"ByteAlign",	wav_pointer->header.blockAlign);
// 	printf("%s\t%u \n",		"BitsPerSample",wav_pointer->header.bitsPerSample);
// 	printf("%s\t%.4s \n",	"Subchunk2ID",	wav_pointer->header.subchunk2ID);
// 	printf("%s\t%u \n",		"Subchunk2Size",wav_pointer->header.subchunk2Size);
// }


void main()
{
	struct Wav* res_pointer = read_wav(INPUT_LOCATION);
	if (res_pointer == NULL) return;
	//print_header(res_pointer);

	adjust_volume(res_pointer, 3.14);

	write_wav(res_pointer, OUTPUT_LOCATION);

	return;
}
