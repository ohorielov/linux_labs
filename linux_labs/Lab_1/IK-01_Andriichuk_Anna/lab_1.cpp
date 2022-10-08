#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#ifndef NULL
#define NULL   ((void *) 0)
#endif


typedef unsigned char byte;

union int_data{
	int int_value;
	byte int_bytes[4];
};
union short_data{
	short short_value;
	byte short_bytes[2];
};
struct wave_header_srtct {
	char chunkId [4];
	union int_data chunkSize;
	char format [4];
	char subChunk1Id [4];
	union int_data subChunk1Size;
	union short_data audioFormat;
	union short_data numChannels;
	union int_data sampleRate;
	union int_data byteRate;
	union short_data blockAlign;
	union short_data bitsPerSample;
	char subChunk2Id [4];
	union int_data subChunk2Size;
};
union header_data{
	byte data[44]; // header size = 44
	struct wave_header_srtct waveHeader;
};


void readHeader(FILE *fil, union header_data *infoBytes, char const *fileName){
	int i;
	for(i=0; i<44 && (infoBytes->data[i] = getc(fil)) !=EOF; i++);


}
void printHeaderInfo (union header_data *infoBytes){
	printf("Chunk Id: %.4s\n", infoBytes->waveHeader.chunkId);
	printf("Chunk Size: %d\n", infoBytes->waveHeader.chunkSize.int_value);
	printf("Format: %.4s\n", infoBytes->waveHeader.format);

	printf("Subchunk 1 Id: %.4s\n", infoBytes->waveHeader.subChunk1Id);
	printf("Subchunk 1 Size: %d\n", infoBytes->waveHeader.subChunk1Size.int_value);
	printf("Audio Format: %d\n", infoBytes->waveHeader.audioFormat.short_value);
	printf("Num Channels: %d\n", infoBytes->waveHeader.numChannels.short_value);
	printf("Sample Rate: %d\n", infoBytes->waveHeader.sampleRate.int_value);
	printf("Byte Rate: %d\n", infoBytes->waveHeader.byteRate.int_value);
	printf("Block Align: %d\n", infoBytes->waveHeader.blockAlign.short_value);
	printf("Bits per Sample: %d\n", infoBytes->waveHeader.bitsPerSample.short_value);

	printf("Subchunk 2 Id: %.4s\n", infoBytes->waveHeader.subChunk2Id);
	printf("Subchunk 2 Size: %d\n", infoBytes->waveHeader.subChunk2Size.int_value);
}

short *readWaveData (FILE *fil, union header_data *infoBytes){
	short *data;
	short NumChannels = infoBytes->waveHeader.numChannels.short_value;
	short BitsPerSample = infoBytes->waveHeader.bitsPerSample.short_value;
	int DataSize = infoBytes->waveHeader.subChunk2Size.int_value;

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

	short NumChannels = infoBytes->waveHeader.numChannels.short_value;
	short BitsPerSample = infoBytes->waveHeader.bitsPerSample.short_value;
	int DataSize = infoBytes->waveHeader.subChunk2Size.int_value;

	int bps = BitsPerSample/8;
	int numSamplesPC = DataSize/bps/NumChannels;

	fwrite(data, sizeof(short), numSamplesPC * NumChannels, fil);
}

void changeVolume (short *data, union header_data *infoBytes){
	short NumChannels = infoBytes->waveHeader.numChannels.short_value;
	short BitsPerSample = infoBytes->waveHeader.bitsPerSample.short_value;
	int DataSize = infoBytes->waveHeader.subChunk2Size.int_value;

	int bps = BitsPerSample/8;
	int numSamplesPC = DataSize/bps/NumChannels;

	int i, j, volume;
	for(i=0; i<NumChannels; i++){
		for (j=0; j<numSamplesPC; j++){
			volume = data[NumChannels*j + i] * 0.3;
			data[NumChannels*j + i] = volume;
		}
	}
}

int main(int argc, char **argv) {
	FILE *file_input , *file_outpute ;
	char const *inputFileName;
	char const *outputFileName;


	inputFileName = "MasterOfPuppets.wav";
	//inputFileName = "Winnie.wav";
	//inputFileName = "sample-6s.wav";

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


	fclose(file_outpute);
	free(data);
	fclose(file_input);
	free(waveHeader);
	return 0;
}
