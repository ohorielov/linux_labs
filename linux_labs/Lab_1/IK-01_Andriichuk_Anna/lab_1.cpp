#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <cstdint>
#ifndef NULL
#define NULL   ((void *) 0)
#endif

#define HEADERSIZE  44

struct wave_header_srtct {
	char chunkId [4];
	uint32_t chunkSize;
	char format [4];
	char subChunk1Id [4];
	uint32_t subChunk1Size;
	uint16_t audioFormat;
	uint16_t numChannels;
	uint32_t sampleRate;
	uint32_t byteRate;
	uint16_t blockAlign;
	uint16_t bitsPerSample;
	char subChunk2Id [4];
	uint32_t subChunk2Size;
};
union header_data{
	uint32_t data[HEADERSIZE];
	struct wave_header_srtct waveHeader;
};


void readHeader(FILE *fil, union header_data *infoBytes, char const *fileName){
	int i;
	for(i=0; i<44 && (infoBytes->data[i] = getc(fil)) !=EOF; i++);


}
void printHeaderInfo (union header_data *infoBytes){
	printf("Chunk Id: %.4s\n", infoBytes->waveHeader.chunkId);
	printf("Chunk Size: %d\n", infoBytes->waveHeader.chunkSize);
	printf("Format: %.4s\n", infoBytes->waveHeader.format);

	printf("Subchunk 1 Id: %.4s\n", infoBytes->waveHeader.subChunk1Id);
	printf("Subchunk 1 Size: %d\n", infoBytes->waveHeader.subChunk1Size);
	printf("Audio Format: %d\n", infoBytes->waveHeader.audioFormat);
	printf("Num Channels: %d\n", infoBytes->waveHeader.numChannels);
	printf("Sample Rate: %d\n", infoBytes->waveHeader.sampleRate);
	printf("Byte Rate: %d\n", infoBytes->waveHeader.byteRate);
	printf("Block Align: %d\n", infoBytes->waveHeader.blockAlign);
	printf("Bits per Sample: %d\n", infoBytes->waveHeader.bitsPerSample);

	printf("Subchunk 2 Id: %.4s\n", infoBytes->waveHeader.subChunk2Id);
	printf("Subchunk 2 Size: %d\n", infoBytes->waveHeader.subChunk2Size);
}

short *readWaveData (FILE *fil, union header_data *infoBytes){
	short *data;
	short NumChannels = infoBytes->waveHeader.numChannels;
	short BitsPerSample = infoBytes->waveHeader.bitsPerSample;
	int DataSize = infoBytes->waveHeader.subChunk2Size;

	int bps = BitsPerSample/8;
	int numSamplesPC = DataSize/bps/NumChannels;

	data = (short *)malloc(numSamplesPC*NumChannels*sizeof(short));

	int i, j;
	short *d = data;
	for(i=0; i<numSamplesPC; i++){
		for (j=0; j<NumChannels; j++){
			if(fread(d, bps, 1, fil) !=1){
				break;
				//err
			}
			d++;
		}
	}

	return data ;
}
void writeWaveData(FILE *fil, union header_data *infoBytes, short *data, char const *fileName){
	fwrite (infoBytes, sizeof(union header_data), 1, fil);

	short NumChannels = infoBytes->waveHeader.numChannels;
	short BitsPerSample = infoBytes->waveHeader.bitsPerSample;
	int DataSize = infoBytes->waveHeader.subChunk2Size;

	int bps = BitsPerSample/8;
	int numSamplesPC = DataSize/bps/NumChannels;

	fwrite(data, sizeof(short), numSamplesPC * NumChannels, fil);
}

void changeVolume (short *data, union header_data *infoBytes){
	short NumChannels = infoBytes->waveHeader.numChannels;
	short BitsPerSample = infoBytes->waveHeader.bitsPerSample;
	int DataSize = infoBytes->waveHeader.subChunk2Size;

	int bps = BitsPerSample/8;
	int numSamplesPC = DataSize/bps/NumChannels;
	float VloumeChangePersentage = 0.3;

	int i, j, volume;
	for(i=0; i<NumChannels; i++){
		for (j=0; j<numSamplesPC; j++){
			volume = data[NumChannels*j + i] * VloumeChangePersentage;
			data[NumChannels*j + i] = volume;
		}
	}
}

inline void closeFile(FILE *file){
	fclose(file);
}

int main(int argc, char **argv) {
	FILE *file_input , *file_outpute ;
	char const *inputFileName;
	char const *outputFileName;


	inputFileName = "MasterOfPuppets.wav";

	file_input = fopen(inputFileName, "r");

	union header_data *waveHeader;
	short *data;

	waveHeader = (union header_data *)malloc(sizeof(union header_data));
	readHeader(file_input, waveHeader, inputFileName);

	printHeaderInfo(waveHeader);

	data  = readWaveData(file_input, waveHeader);

	changeVolume(data, waveHeader);

    outputFileName = "edMasterOfPuppets.wav";
	file_outpute = fopen(outputFileName, "w");
	writeWaveData(file_outpute, waveHeader, data, outputFileName);


	closeFile(file_outpute);
	free(data);
	closeFile(file_input);
	free(waveHeader);
	return 0;
}
