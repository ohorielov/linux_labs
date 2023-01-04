#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "huffman.h"

#define BUFFER_SIZE 1024*4

int main(int argc, char** argv) {
	if (argc != 3) {
		printf("Must have two arguments!\n");
		exit(EXIT_FAILURE);
	}

	FILE* ifp = fopen(argv[1], "rb");
	fseek(ifp, 0, SEEK_END);
	int sz = ftell(ifp);
	rewind(ifp);

	char* input = malloc(sz + 1);
	fread(input, 1, sz, ifp);
	input[sz] = '\0';
	fclose(ifp);

	FILE* ofp = fopen(argv[2], "wb");
	char* output[BUFFER_SIZE] = { 0 };
	int freq[MAX_ASCII] = { 0 };
	int offset = compress(input, output, BUFFER_SIZE, freq);
	fwrite(output, 1, BUFFER_SIZE, ofp);
	fclose(ofp);

	char* decompressed[BUFFER_SIZE] = { 0 };
	decompress(output, decompressed, BUFFER_SIZE, offset, freq);
	
	if (memcmp(input, decompressed, strlen(decompressed)) == 0) {
		printf("CORRECT!\n");
	} else {
		printf("INCORRECT!\nInput:\n%s\nDecompressed:\n%s\n", input, decompressed);
	}

	free(input);

	return 0;
}