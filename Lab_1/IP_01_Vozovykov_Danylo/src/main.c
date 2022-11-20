#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <malloc.h>
#include <math.h>
#include <string.h>

struct WAVHeader
{
	//RIFF chunk description
	long int chunkID;
	long int chunkSize;
	long int format;

	//fmt sub-chunk
	long int subchunk1ID;
	long int subchunk1Size;
	short int audioFormat;
	short int numChannels;
	long int sampleRate;
	long int byteRate;
	short int blockAlign;
	short int bitsPerSample;

	//data
	long int subchunk2ID;
	long int subchunk2Size;
};

int main(int argc, char *argv[])
{
	char* inputoutputWAV = "./../Master Of Puppets.wav";
	char* outputoutputWAV = "./../Output.wav";
	struct WAVHeader header;
	short int* data;
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
	int samplesCount = header.subchunk2Size / sizeof(short int);
	for(int i = 0; i < samplesCount; i++)
	{
		short int sample = *(data + i);
		sample = (short int)(sample * scale);
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
