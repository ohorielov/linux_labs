#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "wav_header.h"


int main(void){   

    FILE *wav_file = fopen("../Master Of Puppets.wav", "r");
    FILE *wav_file_vol_decr = fopen("../Master Of Puppets volume decreased.wav", "w");

    float factor = 0.7;
  
    struct wav_header wh;

    fread(&wh.ChunkID, 4, 1, wav_file);
    fread(&wh.ChunkSize, 4, 1, wav_file);
    fread(&wh.Format, 4, 1, wav_file);

    fread(&wh.Subchunk1ID, 4, 1, wav_file);
    fread(&wh.Subchunk1Size, 4, 1, wav_file);
    fread(&wh.AudioFormat, 2, 1, wav_file);
    fread(&wh.NumChannel, 2, 1, wav_file);
    fread(&wh.SampleRate, 4, 1, wav_file);
    fread(&wh.ByteRate, 4, 1, wav_file);
    fread(&wh.BlockAlign, 2, 1, wav_file);
    fread(&wh.BitsPerSample, 2, 1, wav_file);

    fread(&wh.Subchunk2ID, 4, 1, wav_file);
    fread(&wh.Subchunk2Size, 4, 1, wav_file);


    fwrite(&wh.ChunkID, 4, 1, wav_file_vol_decr);
    fwrite(&wh.ChunkSize, 4, 1, wav_file_vol_decr);
    fwrite(&wh.Format, 4, 1, wav_file_vol_decr);

    fwrite(&wh.Subchunk1ID, 4, 1, wav_file_vol_decr);
    fwrite(&wh.Subchunk1Size, 4, 1, wav_file_vol_decr);
    fwrite(&wh.AudioFormat, 2, 1, wav_file_vol_decr);
    fwrite(&wh.NumChannel, 2, 1, wav_file_vol_decr);
    fwrite(&wh.SampleRate, 4, 1, wav_file_vol_decr);
    fwrite(&wh.ByteRate, 4, 1, wav_file_vol_decr);
    fwrite(&wh.BlockAlign, 2, 1, wav_file_vol_decr);
    fwrite(&wh.BitsPerSample, 2, 1, wav_file_vol_decr);

    fwrite(&wh.Subchunk2ID, 4, 1, wav_file_vol_decr);
    fwrite(&wh.Subchunk2Size, 4, 1, wav_file_vol_decr);

    int16_t buffer;
    int buffer_size = 2;

    while(fread(&buffer, buffer_size, 1, wav_file)){

        buffer *= factor;
        fwrite(&buffer, buffer_size, 1, wav_file_vol_decr);

    }
    
    wav_header_printing(wh);

    fclose(wav_file);
    fclose(wav_file_vol_decr);

	return 0;
}

void wav_header_printing(struct wav_header wh){
    
    printf("ChunkID:%s\n", &wh.ChunkID);
    printf("ChunkSize:%d\n", wh.ChunkSize);
    printf("Format:%s\n", &wh.Format);

    printf("Subchunk1ID:%s\n", &wh.Subchunk1ID);
    printf("Subchunk1Size:%d\n", wh.Subchunk1Size);
    printf("AudioFormat:%d\n", wh.AudioFormat);
    printf("NumChannel:%d\n", wh.NumChannel);
    printf("SampleRate:%d\n", wh.SampleRate);
    printf("ByteRate:%d\n", wh.ByteRate);
    printf("BlockAlign:%d\n", wh.BlockAlign);
    printf("BitsPerSample:%d\n", wh.BitsPerSample);

    printf("Subchunk2ID:%s\n", &wh.Subchunk2ID);
    printf("Subchunk2Size:%d\n", wh.Subchunk2Size);
}

