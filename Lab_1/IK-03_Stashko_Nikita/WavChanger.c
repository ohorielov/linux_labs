#include "WavChanger.h"
#define NumberOfElements 1
#define Bytes2 2
#define Bytes4 4
//Read the .wav file
void WavRead(FILE* file, struct WavHeader* wav_h) 
{
    //fread(Storage location, item size in bytes, maximum number of items, pointer);
    fread(&wav_h->riff.ChunkId, Bytes4, NumberOfElements, file);
    fread(&wav_h->riff.ChunkSize, Bytes4, NumberOfElements, file);
    fread(&wav_h->riff.Format, Bytes4, NumberOfElements, file);
    fread(&wav_h->fmt.Subchunk1Id, Bytes4, NumberOfElements, file);
    fread(&wav_h->fmt.Subchunk1Size, Bytes4, NumberOfElements, file);
    fread(&wav_h->fmt.AudioFormat, Bytes2, NumberOfElements, file);
    fread(&wav_h->fmt.NumChannels, Bytes2, NumberOfElements, file);
    fread(&wav_h->fmt.SampleRate, Bytes4, NumberOfElements, file);
    fread(&wav_h->fmt.ByteRate, Bytes4, NumberOfElements, file);
    fread(&wav_h->fmt.BlockAlign, Bytes2, NumberOfElements, file);
    fread(&wav_h->fmt.BitsPerSample, Bytes2, NumberOfElements, file);
    fread(&wav_h->data.Subchunk2Id, Bytes4, NumberOfElements, file);
    fread(&wav_h->data.Subchunk2Size, Bytes4, NumberOfElements, file);
    wav_h->data.data = malloc(wav_h->data.Subchunk2Size);
    fread(wav_h->data.data, wav_h->data.Subchunk2Size, NumberOfElements, file);
    fclose(file);
}
//Write the .wav file
void WavWrite(FILE* file, struct WavHeader *wav_h) 
{
	//fwrite(Pointer to data to be written, item size in bytes, maximum number of items, pointer to file)
	fwrite(&wav_h->riff.ChunkId, Bytes4, NumberOfElements, file);
	fwrite(&wav_h->riff.ChunkSize, Bytes4, NumberOfElements, file);
	fwrite(&wav_h->riff.Format, Bytes4, NumberOfElements, file);
	fwrite(&wav_h->fmt.Subchunk1Id, Bytes4, NumberOfElements, file);
	fwrite(&wav_h->fmt.Subchunk1Size, Bytes4, NumberOfElements, file);
	fwrite(&wav_h->fmt.AudioFormat, Bytes2, NumberOfElements, file);
	fwrite(&wav_h->fmt.NumChannels, Bytes2, NumberOfElements, file);
	fwrite(&wav_h->fmt.SampleRate, Bytes4, NumberOfElements, file);
	fwrite(&wav_h->fmt.ByteRate, Bytes4, NumberOfElements, file);
	fwrite(&wav_h->fmt.BlockAlign, Bytes2, NumberOfElements, file);
	fwrite(&wav_h->fmt.BitsPerSample, Bytes2, NumberOfElements, file);
	fwrite(&wav_h->data.Subchunk2Id, Bytes4, NumberOfElements, file);
	fwrite(&wav_h->data.Subchunk2Size, Bytes4, NumberOfElements, file);
	fwrite(wav_h->data.data, wav_h->data.Subchunk2Size, NumberOfElements, file);
	fclose(file);
}
//Print information about audio file
void WavPrint(struct WavHeader *wav_h) 
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
//Change audio volume
void VolumeChange(struct WavHeader *wav_h, float scale) 
{
	for (int i = 0; i < wav_h->data.Subchunk2Size / sizeof(short); i++){
    	wav_h->data.data[i] = (short) (wav_h->data.data[i] * scale);
	}
}
