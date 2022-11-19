#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <malloc.h>
#include <math.h>
#include <string.h>

#define COPY(x, y) memcpy(&_##x, testData + a, y); a += y
#define PRINTD(x, y) printf(#x ": %d\n", _##y)
#define PRINTS(x, y) printf(#x ": %s\n", _##y)

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
}_header;

int main(int argc, char *argv[])
{
	_header.cID[4] = 0;
	_header.format[4] = 0;
	_header.s1ID[4] = 0;
	_header.s2ID[4] = 0;
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
        memcpy(&_header.cID, testData, 4);
        int a = 4;
        COPY(header.cSize, 4);
        COPY(header.format, 4);
        COPY(header.s1ID, 4);
        COPY(header.s1Size, 4);
        if (_header.s1Size != 16)
        {
        	fread(testData + a, sizeof(char), (size_t) _header.s1Size + 8, inFD);
        	a += _header.s1Size;
        }
        else
        {
        	fread(testData + a, sizeof(char), (size_t) _header.s1Size + 8, inFD);
        	COPY(header.aFormat, 2);
        	COPY(header.nChannels, 2);
        	COPY(header.sampleR, 4);
        	COPY(header.byteR, 4);
        	COPY(header.blockAlign, 2);
        	COPY(header.bitsPerSample, 2); 	
        }
        COPY(header.s2ID, 4);
        COPY(header.s2Size, 4);  
        free(testData);
        if (a == 44)
        {
        	PRINTS(ChankID, header.cID);
        	PRINTD(ChankSize, header.cSize);
        	PRINTS(Format, header.format);
        	PRINTS(Subchank1ID, header.s1ID);
        	PRINTD(Subchank1Size, header.s1Size);
        	PRINTD(AudioFormat, header.aFormat);
        	PRINTD(NumChannels, header.nChannels);
        	PRINTD(SampleRate, header.sampleR);
        	PRINTD(ByteRate, header.byteR);
        	PRINTD(BlockAlign, header.blockAlign);
        	PRINTD(BitsPerSample, header.bitsPerSample);
        }
        else
        {
        	
        	printf("Unnormal header!\n");
        	PRINTS(ChankID, header.cID);
        	PRINTD(ChankSize, header.cSize);
        	PRINTS(Format, header.format);
        	PRINTS(Subchank1ID, header.s1ID);
        	PRINTD(Subchank1Size, header.s1Size);
        }
        PRINTS(Subchank2ID, header.s2ID);
        PRINTD(Subchank2Size, header.s2Size);
        if (fseek(inFD, 0, SEEK_SET) != 0)
        {
        	printf("Error when reading file!");// %s!\n", argv[1]);
                exit(-1);
        }
	char* readedData = malloc(sizeof(char) * (_header.cSize + 8));
	char* writeData = malloc(sizeof(char) * (_header.cSize + 8));
	fread(readedData, sizeof(char), (size_t) (_header.cSize + 8), inFD);
	fclose(inFD);
	for(int i = 0; i < a; i++)
	{
		writeData[i] = readedData[i];
	}
	for(int i = a; i < _header.s2Size; i++)
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
	fwrite(writeData, sizeof(char), (size_t) (_header.cSize + 8), inFD);
	free(writeData);
	fclose(outFD);
	return 0;
}
