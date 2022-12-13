#include "changerwav.h"
#define NumberOfElements 1
#define bytes2 2
#define bytes4 4

//Change audio volume
void volumechange(struct WavHeader *wav_h, float scale) 
{
	for (int i = 0; i < wav_h->data.Subchunk2Size / sizeof(short); i++){
    	wav_h->data.data[i] = (short) (wav_h->data.data[i] * scale);
	}
}
//Read the .wav file
void read(FILE* file, struct WavHeader* wav_h) 
{
    //fread(Storage location, item size in bytes, maximum number of items, pointer);
    fread(&wav_h->riff.ChunkId, bytes4, NumberOfElements, file);
    fread(&wav_h->riff.ChunkSize, bytes4, NumberOfElements, file);
    fread(&wav_h->riff.Format, bytes4, NumberOfElements, file);
    fread(&wav_h->fmt.Subchunk1Id, bytes4, NumberOfElements, file);
    fread(&wav_h->fmt.Subchunk1Size, bytes4, NumberOfElements, file);
    fread(&wav_h->fmt.AudioFormat, bytes2, NumberOfElements, file);
    fread(&wav_h->fmt.NumChannels, bytes2, NumberOfElements, file);
    fread(&wav_h->fmt.SampleRate, bytes4, NumberOfElements, file);
    fread(&wav_h->fmt.ByteRate, bytes4, NumberOfElements, file);
    fread(&wav_h->fmt.BlockAlign, bytes2, NumberOfElements, file);
    fread(&wav_h->fmt.BitsPerSample, bytes2, NumberOfElements, file);
    fread(&wav_h->data.Subchunk2Id, bytes4, NumberOfElements, file);
    fread(&wav_h->data.Subchunk2Size, bytes4, NumberOfElements, file);
    wav_h->data.data = malloc(wav_h->data.Subchunk2Size);
    fread(wav_h->data.data, wav_h->data.Subchunk2Size, NumberOfElements, file);
    fclose(file);
}

//Print information about audio file
void print(struct WavHeader *wav_h) 
{
        printf("ChunkId: %s\n", wav_h->riff.ChunkId);
	printf("ChunkSize: %d\n", wav_h->riff.ChunkSize);
	printf("Format: %s\n", wav_h->riff.Format);
	printf("Subchunk1Id: %s\n", wav_h->fmt.Subchunk1Id);
	printf("Subchunk1Size: %d\n", wav_h->fmt.Subchunk1Size);
	printf("AudioFormat: %d\n", wav_h->fmt.AudioFormat);
	printf("NumChannels: %d\n", wav_h->fmt.NumChannels);
	printf("SampleRate: %d\n", wav_h->fmt.SampleRate);
	printf("ByteRate: %d\n", wav_h->fmt.ByteRate);
	printf("BlockAlign: %d\n", wav_h->fmt.BlockAlign);
	printf("BitsPerSample: %d\n", wav_h->fmt.BitsPerSample);
	printf("Subchunk2Id: %s\n", wav_h->data.Subchunk2Id);
	printf("Subchunk2Size: %d\n", wav_h->data.Subchunk2Size);
}

//Write the .wav file
void write(FILE* file, struct WavHeader *wav_h) 
{
	//fwrite(Pointer to data to be written, item size in bytes, maximum number of items, pointer to file)
	fwrite(&wav_h->riff.ChunkId, bytes4, NumberOfElements, file);
	fwrite(&wav_h->riff.ChunkSize, bytes4, NumberOfElements, file);
	fwrite(&wav_h->riff.Format, bytes4, NumberOfElements, file);
	fwrite(&wav_h->fmt.Subchunk1Id, bytes4, NumberOfElements, file);
	fwrite(&wav_h->fmt.Subchunk1Size, bytes4, NumberOfElements, file);
	fwrite(&wav_h->fmt.AudioFormat, bytes2, NumberOfElements, file);
	fwrite(&wav_h->fmt.NumChannels, bytes2, NumberOfElements, file);
	fwrite(&wav_h->fmt.SampleRate, bytes4, NumberOfElements, file);
	fwrite(&wav_h->fmt.ByteRate, bytes4, NumberOfElements, file);
	fwrite(&wav_h->fmt.BlockAlign, bytes2, NumberOfElements, file);
	fwrite(&wav_h->fmt.BitsPerSample, bytes2, NumberOfElements, file);
	fwrite(&wav_h->data.Subchunk2Id, bytes4, NumberOfElements, file);
	fwrite(&wav_h->data.Subchunk2Size, bytes4, NumberOfElements, file);
	fwrite(wav_h->data.data, wav_h->data.Subchunk2Size, NumberOfElements, file);
	fclose(file);
}