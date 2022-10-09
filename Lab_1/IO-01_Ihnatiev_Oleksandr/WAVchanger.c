#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <malloc.h>

struct WAV_HEADER
{
	char cID[4];
	long cSize;
	char format[4];
	char s1ID[4];
	long s1Size;
	short aFormat;
	short nChannels;
	long sampleR;
	long byteR;
        short blockAlign;
        short bitsPerSample;
	char s2ID[4];
	long s2Size;
}header;

int main(int argc, char *argv[])
{
	if (argc > 4 || argc < 3)
	{
		printf("Error, uncorrect input!\nCorrect input:\"%s inputFileName outputFileName [-a or -d]\"", argv[0]);
		exit(-1);
	}
	float change = 1.2;
	if(argc == 4)
	{
		if(argv[3][1] == 'd')
		{
			change = 0.8;
		}
		else if(argv[3][1] != 'a')
		{
			printf("Error, uncorrect input!\nCorrect input:\"%s inputFileName outputFileName [-a or -d]\"", argv[0]);
			exit(-1);
		}
	}
	FILE *inFD = fopen(argv[1], "r");
	if (inFD == NULL)
	{
		printf("Error when opening file %s!\n", argv[1]);
                exit(-1);
	}
        fread(&header.cID, 4, 1, inFD);
        printf("ChunkID: %s", header.cID);
        fread(&header.cSize, 4, 1, inFD);
	printf(";\nChunkSize: %d", header.cSize);
	fread(&header.format, 4, 1, inFD);
        printf(";\nFormat: %s", header.format);
        fread(&header.s1ID, 4, 1, inFD);
	printf(";\nSubchunk1ID: %s", header.s1ID);
	fread(&header.s1Size, 4, 1, inFD);
	printf(";\nSubchunk1Size: %d", header.s1Size);
	fread(&header.aFormat, 2, 1, inFD);         
	printf(";\nAudioFormat: %d", header.aFormat);
	fread(&header.nChannels, 2, 1, inFD);
        printf(";\nNumChannels: %d", header.nChannels);
        fread(&header.sampleR, 4, 1, inFD);
        printf(";\nSampleRate: %d", header.sampleR);
        fread(&header.byteR, 4, 1, inFD);
      	printf(";\nByteRate: %d", header.byteR);
      	fread(&header.blockAlign, 2, 1, inFD);
        printf(";\nBlockAlign: %d", header.blockAlign);
        fread(&header.bitsPerSample, 2, 1, inFD);
        printf(";\nBitsPerSample: %d", header.bitsPerSample);
        fread(&header.s2ID, 4, 1, inFD);
        printf(";\nSubchunk2ID: %s", header.s2ID);
        fread(&header.s2Size, 4, 1, inFD);
        printf(";\nSubchunk2Size: %d.\n", header.s2Size);
        if (fseek(inFD, 0, SEEK_SET) != 0)
        {
        	printf("Error when reading file %s!\n", argv[1]);
                exit(-1);
        }
	char* readedData = malloc(sizeof(char) * (header.s2Size + 44));
	char* writeData = malloc(sizeof(char) * (header.s2Size + 44));
	fread(readedData, sizeof(char), (size_t) (header.s2Size + 44), inFD);
	fclose(inFD);
	for(int i = 0; i < 44; i++)
	{
		writeData[i] = readedData[i];
	}
	for(int i = 44; i < header.s2Size; i++)
	{
		writeData[i] = readedData[i] * change;							
	}
	free(readedData);
	FILE *outFD = fopen(argv[2], "w");
	if (outFD == NULL)
	{
		free(writeData);
		printf("Error when opening file %s!\n", argv[2]);
                exit(-1);
	}
	fwrite(writeData, sizeof(char), (size_t) (header.s2Size + 44), inFD);
	free(writeData);
	fclose(outFD);
	return 0;
}
