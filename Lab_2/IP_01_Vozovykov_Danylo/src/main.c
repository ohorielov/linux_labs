#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CHARS 256
#include "encoder.h"
#include "decoder.h"

int main(int argc, char *argv[])
{
	if(argc < 3 || argc > 4)
	{
		printf("Use this arguments: [txt_to_compress] [compress_file_bin] (Optional)[decompress_txt]\n");
		return 0;
	}

	FILE* inputFile = fopen(argv[1], "rb");
	FILE* outputFile = fopen(argv[2], "wb");

	if(inputFile == NULL)
	{
		printf("Couldnt find txt to compress. Please check first argument\n");
		return -2;
	}

	if(outputFile == NULL)
	{
		printf("Couldnt create bin to compress to. Please check second argument\n");
		return -2;
	}

	compress(inputFile, outputFile);

	fclose(inputFile);
	fclose(outputFile);

	if(argc > 3)
	{
		FILE* inputFileDec = fopen(argv[2], "rb");
		FILE* outputFileDec = fopen(argv[3], "wb");

		if(outputFileDec == NULL)
		{
			printf("Couldnt create txt to decompress to. Please check third argument\n");
			return -2;
		}

		decompress(inputFileDec, outputFileDec);

		fclose(inputFileDec);
		fclose(outputFileDec);

		//check text file streams
		FILE* original = fopen(argv[1], "rb");
		FILE* decompress = fopen(argv[3], "rb");

		int result = compare(original, decompress);

		fclose(original);
		fclose(decompress);

		return result;
	}

	return 0;
}

int compare(FILE* inputFile1, FILE* inputFile2)
{
	fseek(inputFile1, 0, SEEK_END);
	int textLengthF1 = ftell(inputFile1);
	fseek(inputFile1, 0, SEEK_SET);
	char* text1 = malloc(textLengthF1);
	fread (text1, 1, textLengthF1, inputFile1);

	fseek(inputFile2, 0, SEEK_END);
	int textLengthF2 = ftell(inputFile2);
	fseek(inputFile2, 0, SEEK_SET);
	char* text2 = malloc(textLengthF2);
	fread (text2, 1, textLengthF2, inputFile2);

	if(textLengthF1 != textLengthF2)
		return -4;

	for(int i = 0; i < textLengthF1; i++)
	{
		if(text1[i] != text2[i])
		{
			printf("Failed. Files are different: %c != %c", text1[i], text2[i]);
			return -3;
		}

	}

	return 0;
}
