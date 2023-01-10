#include "decoder.h"

#ifndef MAX_CHARS
#define MAX_CHARS 256
#endif

void decompress(FILE* inputFile, FILE* outputFile)
{
	int freq[MAX_CHARS] = {0};
	int uniqueChars = 0;
	int textLength = 0;
	readHeader(inputFile, freq, &uniqueChars, &textLength);

	TreeNode* root = buildTree(freq);

	char* outputText = malloc(textLength);
	readCompressedText(inputFile, root, outputText, textLength);

	fwrite(outputText, sizeof(char), textLength, outputFile);

	freeTree(root);
}

void readHeader(FILE* inputFile, int freq[MAX_CHARS], uint8_t* uniqueChars, int* textLength)
{
	fread(textLength, sizeof(int), 1, inputFile);
	fread(uniqueChars, sizeof(int), 1, inputFile);

	for (int i = 0; i < (*uniqueChars); i++)
	{
		uint8_t targetChar;
		int frequancy;
		fread(&targetChar, sizeof(uint8_t), 1, inputFile);
		fread(&frequancy, sizeof(int), 1, inputFile);
		freq[targetChar] = frequancy;
	}
}

void readCompressedText(FILE* inputFile, TreeNode* root, char* outputText, int textLength)
{
	uint16_t mask = 0;
	uint16_t readByte = 0;
	uint16_t caryByte;

	uint8_t leftBitShifts, readBitsAmount;
	short caryBitPointer;

	int outputIterator = 0;

	fread(&readByte, sizeof(uint16_t), 1, inputFile);
	leftBitShifts = 15;
	caryBitPointer = -1;
	readBitsAmount = 0;

	TreeNode* currentNode;

	for(int i = 0; i < textLength; i++)
	{
		currentNode = root;

		while(currentNode != NULL)
		{
			mask = 1 << leftBitShifts;
			leftBitShifts--;
			readBitsAmount++;
			if( (readByte & mask) > 0)
			{
				currentNode = currentNode->right;
			}
			else
			{
				currentNode = currentNode->left;
			}

			if(currentNode == NULL)
			{
				perror("Failed to read bit sequence");
			}

			if (currentNode->ch != '\0')
			{
				outputText[outputIterator++] = currentNode->ch;
				break;
			}
		}

		//read bit from cary byte
		mask = 0;
		while(readBitsAmount > 0)
		{
			if(caryBitPointer < 0)
			{
				caryBitPointer = 15;
				fread(&caryByte, sizeof(uint16_t), 1, inputFile);
			}

			mask = 1 << caryBitPointer;
			readByte = (readByte << 1) + ((caryByte & mask) >> caryBitPointer);

			readBitsAmount--;
			caryBitPointer--;
		}

		leftBitShifts = 15;
		mask = 0;
	}
}
