#include "encoder_decoder.h"

#define decoded_text "./decoded.txt"

HashMap mp;
FILE* readTable(FILE *file) {
	unsigned int element = 0;
	fread(&element, sizeof(element), 1, file);

	for (int i = 0; i < element; i++) {
		unsigned char ch;
		unsigned char size;
		unsigned long long code;

		fread(&ch, sizeof(ch), 1, file);
		fread(&size, sizeof(size), 1, file);
		fread(&code, sizeof(code), 1, file);
		insertMap(&mp, code, size, ch);
	}

	return file;
}

void decompress(char *filename) {
	FILE *file = fopen(filename, "rb");
	FILE *out = fopen(decoded_text, "wb");

	initMap(&mp);

	file = readTable(file);

	int writtenBits;
	fread(&writtenBits, sizeof(writtenBits), 1, file);

	unsigned char ch;
	unsigned long long buffer = 0;
	unsigned long long bufferSize = 0;
	
	int checkedBits = 0;
	while (fread(&ch, sizeof(ch), 1, file) != EOF) {
		for (int i = 7; i >= 0; i--) {
			checkedBits++;

			if (ch &(1 << i)) {
				buffer |= (1 << bufferSize);
			}

			bufferSize++;
			if (findMap(mp, buffer, bufferSize) != INT_MIN) {
				char ch = findMap(mp, buffer, bufferSize);
				fprintf(out, "%c", ch);
				buffer = 0;
				bufferSize = 0;
			}

			if (checkedBits == writtenBits) {
				fclose(out);
				fclose(file);

				return;
			}
		}
	}

	fclose(out);
	fclose(file);
}

int countNoofWrittenBits(char *filename, HuffEncoder e) {
	FILE *in = fopen(filename, "r");

	int writtenBits = 0;
	unsigned char ch;

	while (fscanf(in, "%c", &ch) != EOF) {
		writtenBits += (int)e.lengths[(int)ch];
	}

	fclose(in);

	return writtenBits;
}

FILE* tableWriter(char *filename, FILE *output, HuffEncoder e) {
	unsigned int sum = 0;

	for (int i = 0; i < ENTRIES_SIZE; i++) {
		if (e.lengths[i] != 0) {
			sum++;
		}
	}

	fwrite(&sum, sizeof(sum), 1, output);
	for (int i = 0; i < ENTRIES_SIZE; i++) {
		if (e.lengths[i]) {
			unsigned char ch = i;
			fwrite(&ch, sizeof(ch), 1, output);
			ch = e.lengths[i];
			fwrite(&ch, sizeof(ch), 1, output);
			unsigned long long code = e.codeWords[i];
			fwrite(&code, sizeof(code), 1, output);
		}
	}

	int bitswritten = countNoofWrittenBits(filename, e);
	fwrite(&bitswritten, sizeof(bitswritten), 1, output);

	return output;
}

int countEntries(char *filename, int *entries) {
	FILE *file = fopen(filename, "r");

	if (!file) {
		printf("Can't Open file\n");
		return 0;
	}

	unsigned char ch;

	while (fscanf(file, "%c", &ch) != EOF) {
		entries[(int)ch]++;
	}

	fclose(file);

	return 1;
}

void createFile(char *filename, HuffEncoder e) {
	FILE *in = fopen(filename, "r");
	FILE *out = fopen(compressed_text, "wb");

	out = tableWriter(filename, out, e);
	unsigned char ch;
	unsigned char buffer = 0;
	int currentBit = 7;

	while (fscanf(in, "%c", &ch) != EOF) {
		unsigned long long code = e.codeWords[(int) ch];
		int sz = e.lengths[(int) ch];
		for (int i = 0; i < sz; i++) {
			if (code &(1ll << i)) {
				buffer |= (1 << currentBit);
			}

			currentBit--;
			if (currentBit < 0) {
				fwrite(&buffer, sizeof(buffer), 1, out);
				buffer = 0;
				currentBit = 7;
			}
		}
	}

	if (currentBit != 7) {
		fwrite(&buffer, sizeof(buffer), 1, out);
	}

	fclose(in);
	fclose(out);
}

void compress(char *filename) {
	int *entries = (int*) malloc(sizeof(int) *ENTRIES_SIZE);

	for (int i = 0; i < ENTRIES_SIZE; i++) {
		entries[i] = 0;
	}

	if (!countEntries(filename, entries)) {
		return;
	}

	HuffEncoder e;
	encoderInitialize(&e, entries, ENTRIES_SIZE);
	createFile(filename, e);
}
