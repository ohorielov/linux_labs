#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <malloc.h>
#include <math.h>
#include <string.h>

struct WAVheader
{
	char cID[5];
	long int cSize;
	char format[5];
	char s1ID[5];
	long int s1Size;
	short int aFormat;
	short int nChannels;
	long int sampleR;
	long int byteR;
        short int blockAlign;
        short int bitsPerSample;
	char s2ID[5];
	long int s2Size;
}header;

int main(int argc, char *argv[])
{
	header.cID[4] = 0;
	header.format[4] = 0;
	header.s1ID[4] = 0;
	header.s2ID[4] = 0;
	/*if (argc > 4 || argc < 3)
	{
		printf("Error, uncorrect input!\nCorrect input:\"%s inputFileName outputFileName [-a or -d]\"", argv[0]);
		exit(-1);
	}*/
	float change = -2;
	/*if(argc == 4)
	{
		if(argv[3][1] == 'd')
		{
			change = -2;
		}
		else if(argv[3][1] != 'a')
		{
			printf("Error, uncorrect input!\nCorrect input:\"%s inputFileName outputFileName [-a or -d]\"", argv[0]);
			exit(-1);
		}
	}*/
	FILE *inFD = fopen("./Master Of Puppets.wav"/*argv[1]*/, "r");
	if (inFD == NULL)
	{
		printf("Error when opening file!");// %s!\n", argv[1]);
                exit(-1);
	}
	char* testData = malloc(sizeof(char) * (100));
	fread(testData, sizeof(char), (size_t) 20, inFD);
        memcpy(&header.cID, testData, 4);
        int a = 4;
        memcpy(&header.cSize, testData + a, 4);
        a += 4;
        memcpy(&header.format, testData + a, 4);
        a += 4;
        memcpy(&header.s1ID, testData + a, 4);
        a += 4;
        memcpy(&header.s1Size, testData + a, 4);
        a += 4;
        if (header.s1Size != 16)
        {
        	fread(testData + a, sizeof(char), (size_t) header.s1Size + 8, inFD);
        	a += header.s1Size;
        }
        else
        {
        	fread(testData + a, sizeof(char), (size_t) header.s1Size + 8, inFD);
        	memcpy(&header.aFormat, testData + a, 2); 
        	a += 2;        
        	memcpy(&header.nChannels, testData + a, 2);
        	a += 2;
        	memcpy(&header.sampleR, testData + a, 4);
        	a += 4;
        	memcpy(&header.byteR, testData + a, 4);
        	a += 4;
        	memcpy(&header.blockAlign, testData + a, 2);
        	a += 2;
        	memcpy(&header.bitsPerSample, testData + a, 2);
        	a += 2;
        	
        }
        memcpy(&header.s2ID, testData + a, 4);
        a += 4;
        memcpy(&header.s2Size, testData + a, 4); 
        a += 4;      
        free(testData);
        if (a == 44)
        {
        	printf("ChunkID: %s;\nChunkSize: %d;\nFormat: %s;\nSubchunk1ID: %s;\nSubchunk1Size: %d;\nAudioFormat: %d;\nNumChannels: %d;\nSampleRate: %d;\nByteRate: %d;\nBlockAlign: %d;\nBitsPerSample: %d;\nSubchunk2ID: %s;\nSubchunk2Size: %d.\n", header.cID, header.cSize, header.format, header.s1ID, header.s1Size, header.aFormat, header.nChannels, header.sampleR, header.byteR, header.blockAlign, header.bitsPerSample, header.s2ID, header.s2Size);
        }
        else
        {
        	printf("Unnormal header!\nChunkID: %s;\nChunkSize: %d;\nFormat: %s;\nSubchunk1ID: %s;\nSubchunk1Size: %d;\nSubchunk2ID: %s;\nSubchunk2Size: %d.\n", header.cID, header.cSize, header.format, header.s1ID, header.s1Size, header.s2ID, header.s2Size);
        }
        if (fseek(inFD, 0, SEEK_SET) != 0)
        {
        	printf("Error when reading file!");// %s!\n", argv[1]);
                exit(-1);
        }
	char* readedData = malloc(sizeof(char) * (header.cSize + 8));
	char* writeData = malloc(sizeof(char) * (header.cSize + 8));
	fread(readedData, sizeof(char), (size_t) (header.cSize + 8), inFD);
	fclose(inFD);
	for(int i = 0; i < a; i++)
	{
		writeData[i] = readedData[i];
	}
	for(int i = a; i < header.s2Size; i++)
	{
		writeData[i] = readedData[i] * pow(10, 0.05 * change);							
	}
	free(readedData);
	FILE *outFD = fopen("./TestDown.wav"/*argv[2]*/, "w");
	if (outFD == NULL)
	{
		free(writeData);
		printf("Error when opening file!");// %s!\n", argv[2]);
                exit(-1);
	}
	fwrite(writeData, sizeof(char), (size_t) (header.cSize + 8), inFD);
	free(writeData);
	fclose(outFD);
	return 0;
}
