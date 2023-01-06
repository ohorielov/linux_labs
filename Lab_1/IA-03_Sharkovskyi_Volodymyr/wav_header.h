#include <stdio.h>

struct wav_header{
    int32_t *fmtSubChunk;

	//RIFF
	char ChunkID[4];
	int32_t ChunkSize;
	char Format[4];
	//WAVE
	char Subchunk1ID[4];
	int32_t Subchunk1Size;
	int16_t AudioFormat;
	int16_t NumChannel;
	int32_t SampleRate;
	int32_t ByteRate;
	int16_t BlockAlign;
	int16_t BitsPerSample;
		//data
	char Subchunk2ID[4];
	int32_t Subchunk2Size;
	int16_t *data;
};