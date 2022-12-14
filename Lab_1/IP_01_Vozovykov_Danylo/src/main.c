#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <malloc.h>
#include <math.h>
#include <stdint.h>
#include <string.h>

struct WAVHeader
{
	//RIFF chunk description
	uint32_t chunkID;
	uint32_t chunkSize;
	uint32_t format;

	//fmt sub-chunk
	uint32_t subchunk1ID;
	uint32_t subchunk1Size;
	uint16_t audioFormat;
	uint16_t numChannels;
	uint32_t sampleRate;
	uint32_t byteRate;
	uint16_t blockAlign;
	uint16_t bitsPerSample;

	//data
	uint32_t subchunk2ID;
	uint32_t subchunk2Size;
};

int main(int argc, char *argv[])
{
	char* inputoutputWAV = "./../Master Of Puppets.wav";
	char* outputoutputWAV = "./../Output.wav";
	struct WAVHeader header;
	uint16_t* data;
	float scale = 1.4;

	if(argc < 2)
	{
		printf("Running arguments: [Path to input wav] [Path to output wav] [scale]\n");
		printf("Example: \"./Master Of Puppets.wav\" ./Output.wav 1.4\n");
		printf("Arguments were not provided. Using default arguments.\n");
	}
	else
	{
		inputoutputWAV = malloc(strlen(argv[1]) + 1);
		outputoutputWAV = malloc(strlen(argv[2]) + 1);
		strcpy(inputoutputWAV, argv[1]);
		strcpy(outputoutputWAV, argv[2]);
		scale = atof(argv[3]);
	}

	//Read header
	FILE* inputWAV = fopen(inputoutputWAV, "rb");
	if (inputWAV == NULL)
	{
		printf("Can't open %s file\n", inputoutputWAV);
		exit(-1);
	}

	fread(&header, sizeof(struct WAVHeader), 1, inputWAV);
	data = malloc(header.subchunk2Size);
	fread(data, header.subchunk2Size, 1, inputWAV);
	fclose(inputWAV);

	printf("Amplifying '%s' with scale %.2f\n", inputoutputWAV, scale);
	//Amplify wav
	int samplesCount = header.subchunk2Size / sizeof(int16_t);
	for(int i = 0; i < samplesCount; i++)
	{
		int16_t sample = *(data + i);
		sample = (int16_t)(sample * scale);
		data[i] = sample;
	}

	printf("Writing results to '%s'\n", outputoutputWAV);
	//Output wav file
	FILE* outputWAV = fopen(outputoutputWAV, "wb");
	if (outputWAV == NULL)
	{
		free(data);
		printf("Can't create %s file", outputoutputWAV);
		exit(-1);
	}

	fwrite(&header, sizeof(struct WAVHeader), 1, outputWAV);
	fwrite(data, header.subchunk2Size, 1, outputWAV);
	fclose(outputWAV);

	free(data);
	printf("Successful");
	return 0;
}
