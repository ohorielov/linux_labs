#include <stdio.h>

typedef struct wav_header{
	//RIFF
	size_t ChunkID;
	size_t ChunkSize;
	size_t Format;
	//WAVE
	size_t Subchunk1ID;
	size_t Subchunk1Size;
	size_t AudioFormat;
	size_t NumChannel;
	size_t SampleRate;
	size_t ByteRate;
	size_t BlockAlign;
	size_t BitsPerSample;
		//data
	size_t Subchunk2ID;
	size_t Subchunk2Size;
	short* data;
};