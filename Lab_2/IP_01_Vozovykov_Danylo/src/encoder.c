#include "encoder.h"

#ifndef MAX_CHARS
#define MAX_CHARS 256
#endif

// Compresses the text in the input file and writes it to the output file
void compress(FILE* inputFile, FILE* outputFile)
{
	fseek(inputFile, 0, SEEK_END);
	int textLength = ftell(inputFile);
	fseek(inputFile, 0, SEEK_SET);
	char* text = malloc(textLength);
	fread (text, 1, textLength, inputFile);

	int i = 0;
	// Create a frequency table for the characters in the text
	int freq[MAX_CHARS] = {0};
	int uniqueChars = 0;
	for (i = 0; i < textLength; i++)
	{
		uint8_t cNum = (uint8_t) text[i];

		if(freq[cNum] == 0)
			uniqueChars++;

		freq[cNum]++;
	}

	TreeNode* root = buildTree(freq);

	char* codeTable[MAX_CHARS] = {0};
	buildCodeTable(root, codeTable, "");

	writeHeader(outputFile, freq, uniqueChars, textLength);
	writeCompressedText(outputFile, codeTable, text, textLength);

	freeTree(root);
}



void buildCodeTable(TreeNode* root, char* codeTable[MAX_CHARS], char* prefix)
{
	if (root == NULL)
	{
		return;
	}

	if (root->ch != '\0')
	{
		uint8_t cNum = (uint8_t) root->ch;

		codeTable[cNum] = strdup(prefix);
	}

	char* prefLeft = malloc(strlen(prefix) + 2);
	strcpy(prefLeft, prefix);
	strcat(prefLeft, "0");
	buildCodeTable(root->left, codeTable, prefLeft);
	free(prefLeft);

	char* prefRight = malloc(strlen(prefix) + 2);
	strcpy(prefRight, prefix);
	strcat(prefRight, "1");
	buildCodeTable(root->right, codeTable, prefRight);
	free(prefRight);
}

void writeCompressedText(FILE* outputFile, char* codeTable[MAX_CHARS], char* text, int textLength)
{
	int i;
	uint8_t fillCounter = 0;
	uint16_t writeByte = 0;
	for (i = 0; i < textLength; i++)
	{
		char* code = codeTable[(uint8_t) text[i]];

		if(code == NULL)
		{
			perror("Unknown character!");
			return;
		}

		for(int j = 0; j < strlen(code); j++){
			writeByte = writeByte << 1;
			if(code[j] == '1'){
				writeByte += 1;
			}
			fillCounter++;
			//writeByte when its full
			if(fillCounter >= 16)
			{
				fwrite(&writeByte, sizeof(uint16_t), 1, outputFile);
				fillCounter = 0;
				writeByte = 0;
			}
		}
	}

	if(fillCounter != 0)
	{
		while(fillCounter < 16)
		{
			fillCounter++;
			writeByte <<= 1;
		}
		fwrite(&writeByte, sizeof(uint16_t), 1, outputFile);
	}
}

void writeHeader(FILE* outputFile, int freqauncyTable[MAX_CHARS], int uniqueChars, int textLength)
{
	int j = 0;
	fwrite(&textLength, sizeof(int), 1, outputFile);
	fwrite(&uniqueChars, sizeof(int), 1, outputFile);
	for (int i = 0; i < MAX_CHARS; i++)
	{
		if (freqauncyTable[i] == 0)
			continue;

		int freq = freqauncyTable[i];
		j++;
		fwrite(&i, sizeof(uint8_t), 1, outputFile);
		fwrite(&freq, sizeof(int), 1, outputFile);
	}
	j++;
}
