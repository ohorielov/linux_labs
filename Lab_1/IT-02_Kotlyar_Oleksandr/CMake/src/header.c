#include "Header.h"

const int HEADER_SIZE = 44;
#define file_nameOnput "Master Of Puppets.wav"
#define file_nameOutput "Master Output.wav"
#define k 2

void read_wav(Wav* wav)
{
    FILE* fileIn = fopen(file_nameOnput, "rb");
    if (fileIn == NULL) {
        printf("Can't open");
        return 0;
    }

    fread(&wav->riff, 12, 1, fileIn);
    fread(&wav->fmt, 24, 1, fileIn);
    fread(&wav->data, 8, 1, fileIn);
    wav->data._data = (uint16_t*)malloc(wav->data.Subchunk2Size);
    fread(wav->data._data, wav->data.Subchunk2Size, 1, fileIn);

    fclose(fileIn);

}


long int findSize(char file_name[])
{
    FILE* fp = fopen(file_name, "r");

    if (fp == NULL)
    {
        printf("File Not Found!\n");
        return -1;
    }
    fseek(fp, 0L, SEEK_END);
    long int res = ftell(fp);

    fclose(fp);
    return res;
}



void out_wav(Wav* wav, int size_of_file) {

    // printf("ChunkID \t%c%c%c%c\n", wav->riff.ChunkID[0], wav->riff.ChunkID[1], wav->riff.ChunkID[2], wav->riff.ChunkID[3]);
    FILE* fileOut = fopen(file_nameOutput, "wb");


    int samle_index = (size_of_file - 44) / sizeof(uint16_t);

    fwrite(&wav->riff, 12, 1, fileOut);
    fwrite(&wav->fmt, 24, 1, fileOut);
    fwrite(&wav->data, 8, 1, fileOut);

    for (uint32_t i = 0; i < samle_index; i++) {
        uint16_t sample = wav->data._data[i];
        sample *= k;
        wav->data._data[i] = sample;
    }


    fwrite(wav->data._data, size_of_file - 44, 1, fileOut);
    fclose(fileOut);
}


int main()
{
    Wav* wav = (Wav*)malloc(sizeof(wav));
    RIFF riff;
    FMT fmt;
    Data data;

    long int file_size = findSize(file_nameOnput);
    if (file_size != -1)
        printf("Size of the file - %ld bytes \n\n", file_size);

    read_wav(wav);


    riff = wav->riff;
    fmt = wav->fmt;
    data = wav->data;


    printf("ChunkID \t%c%c%c%c\n", riff.ChunkID[0], riff.ChunkID[1], riff.ChunkID[2], riff.ChunkID[3]);
    printf("ChunkSize \t%d\n", riff.ChunkSize);
    printf("Format \t\t%c%c%c%c\n", riff.Format[0], riff.Format[1], riff.Format[2], riff.Format[3]);

    printf("\n");

    printf("Subchunk1ID \t%c%c%c%c\n", fmt.Subchunk1ID[0], fmt.Subchunk1ID[1], fmt.Subchunk1ID[2], fmt.Subchunk1ID[3]);
    printf("Subchunk1Size \t%d\n", fmt.Subchunk1Size);
    printf("AudioFormat \t%d\n", fmt.AudioFormat);
    printf("NumChannels \t%d\n", fmt.NumChannels);
    printf("SampleRate \t%d\n", fmt.SampleRate);
    printf("ByteRate \t%d\n", fmt.ByteRate);
    printf("BlockAlign \t%d\n", fmt.BlockAlign);
    printf("BitsPerSample \t%d\n", fmt.BitsPerSample);

    printf("\n");

    printf("blockID \t%c%c%c%c\n", data.Subchunk2ID[0], data.Subchunk2ID[1], data.Subchunk2ID[2], data.Subchunk2ID[3]);
    printf("blockSize \t%d\n", data.Subchunk2Size);

    printf("\n");

    printf("duration \t%d\n", data.Subchunk2Size / fmt.ByteRate);


    out_wav(wav, file_size);

    //free(data._data);
   // free(wav);
}