#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

struct WAVHeader {
    char chunkID[4];
    uint32_t chunkSize;
    char format[4];
    char subchunk1ID[4];
    uint32_t subchunk1Size;
    uint16_t audioFormat;
    uint16_t numChannels;
    uint32_t sampleRate;
    uint32_t byteRate;
    uint16_t blockAlign;
    uint16_t bitsPerSample;
    char subchunk2ID[4];
    uint32_t subchunk2Size;
};

void readWAVHeader(const char* fileName, struct WAVHeader* header) {
	FILE *file = fopen(fileName, "rb");
	fread(header, sizeof(struct WAVHeader), 1, file);

	printf("WAV File Header read:\n");
	printf("File Type: %s\n", header -> chunkID);
	printf("File Size: %i\n", header -> chunkSize);
	printf("WAV Marker: %s\n", header -> format);
	printf("Format Name: %s\n", header -> subchunk1ID);
	printf("Format Length: %i\n", header ->subchunk1Size );
	printf("Format Type: %i\n", header -> audioFormat);
	printf("Number of Channels: %i\n", header -> numChannels);
	printf("Sample Rate: %i\n", header -> sampleRate);
	printf("Sample Rate * Bits/Sample * Channels / 8: %i\n", header -> byteRate);
	printf("Bits per Sample * Channels / 8.1: %i\n", header -> blockAlign);
	printf("Bits per Sample: %i\n", header -> bitsPerSample);

	fclose(file);
	printf("WAVHeader read successful.\n");
}

int main(){
	
	struct WAVHeader header;
	readWAVHeader("Master Of Puppets.wav", &header);
	int dataSize = header.subchunk2Size / 2;
	uint16_t* data = (uint16_t*) malloc(dataSize * sizeof(uint16_t));
	FILE *file = fopen("Master Of Puppets.wav", "rb");
	fseek(file, sizeof(struct WAVHeader), SEEK_SET);
	fread(data, sizeof(uint16_t), dataSize, file);
	fclose(file);
	
	printf("\nFILE read successful.\n");

	float scalingFactor = 1.2589; 
	for (int i = 0; i < dataSize; i++){
		data[i] = (uint16_t)(data[i] * scalingFactor);
	}

	FILE *output = fopen("ReMaster Of Puppets.wav", "wb");
	fwrite(&header, sizeof(struct WAVHeader), 1, output);
	fwrite(data, sizeof(uint16_t), dataSize, output);
	fclose(output);

	printf("FILE write successful.\n");
	printf("Warning: LOUD!\n");
	free(data);
	return 0;
}
