#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "wav_header.h"

int main(void){   

    FILE *wav_file = fopen("../Master Of Puppets.wav", "r");
    FILE *wav_file_vol_decr = fopen("../build/Master Of Puppets volume decreased.wav", "w");
      
    struct wav_header wh;

    // 3дб=10lg(x) => x=10^(3/10) => x=2
    // зменшення гучності на 3 дб зменшує потужність вдвічі, а отже амплітуду треба зменшити на обернений корінь з двох разів
    
    float factor = 1 / sqrt(powf(10, 0.3));

    char ChunkID[4] = "RIFF";
    char Format[4] = "WAVE";
    char Subchunk1ID[4] = "fmt";
    char Subchunk2ID[4] = "data";

    int32_t buffer4bytes;
    int16_t buffer2bytes;

    int32_t *fmtSubChunk;
    int16_t *dataSubChunk;


    fread(&wh.ChunkID, 4, 1, wav_file);

    if(strncmp(wh.ChunkID, ChunkID, 4) == 0){

        printf("ChunkID is correct.\n");
        fread(&wh.ChunkSize, 4, 1, wav_file);

        fread(&wh.Format, 4, 1, wav_file);
        if(strncmp(wh.Format, Format, 4) == 0){

            printf("Format is correct.\n");
            fread(&wh.Subchunk1ID, 4, 1, wav_file);

            if(strncmp(wh.Subchunk1ID, Subchunk1ID, 3) == 0){
                
                printf("Subchunk1ID is correct.\n");

                fread(&wh.Subchunk1Size, 4, 1, wav_file);

                fmtSubChunk = (int32_t *)malloc(wh.Subchunk1Size);
                fread(fmtSubChunk, wh.Subchunk1Size, 1, wav_file);

                wh.fmtSubChunk = malloc(wh.Subchunk1Size);
                wh.fmtSubChunk = fmtSubChunk;

                fread(&wh.Subchunk2ID, 4, 1, wav_file);

                if(strncmp(wh.Subchunk2ID, Subchunk2ID, 4) == 0){

                    printf("Subchunk2ID is correct.\n");
                    fread(&wh.Subchunk2Size, 4, 1, wav_file);
                    
                    dataSubChunk = malloc(wh.Subchunk2Size);
                    fread(dataSubChunk, wh.Subchunk2Size, 1, wav_file);

                    wh.data = malloc(wh.Subchunk2Size);
                    wh.data = dataSubChunk;

                    for(int i = 0; i < wh.Subchunk2Size / 2; i++){
                        *(dataSubChunk + i) *= factor;
                    }

                    wh.AudioFormat = *(fmtSubChunk);
                    wh.NumChannel = *(fmtSubChunk) >> 16;
                    wh.SampleRate = *(fmtSubChunk + 1);
                    wh.ByteRate = *(fmtSubChunk + 2);
                    wh.BlockAlign = *(fmtSubChunk + 3);
                    wh.BitsPerSample = *(fmtSubChunk + 3) >> 16;

                } else {
                    printf("Subchunk2ID is not correct.\n");
                    return -1;
                }
            } else {
                printf("Subchunk1ID is not correct.\n");   
                return -1; 
            }
        } else {
            printf("Format is not correct.\n");
            return -1;
        }
    } else {
        printf("ChunkID is not correct.\n");
        return -1;
    }

                    
    fwrite(&wh.ChunkID, 4, 1, wav_file_vol_decr);
    fwrite(&wh.ChunkSize, 4, 1, wav_file_vol_decr);
    fwrite(&wh.Format, 4, 1, wav_file_vol_decr);

    fwrite(&wh.Subchunk1ID, 4, 1, wav_file_vol_decr);
    fwrite(&wh.Subchunk1Size, 4, 1, wav_file_vol_decr);

    for(int i = 0; i < 4; i++){
        buffer4bytes = *(fmtSubChunk + i);
        fwrite(&buffer4bytes, 4, 1, wav_file_vol_decr);
    }

    fwrite(&wh.Subchunk2ID, 4, 1, wav_file_vol_decr);
    fwrite(&wh.Subchunk2Size, 4, 1, wav_file_vol_decr);

    for(int i = 0; i <= wh.Subchunk2Size / 2; i++){
        buffer2bytes = *(wh.data + i);
        fwrite(&buffer2bytes, 2, 1, wav_file_vol_decr);
    }

    fclose(wav_file);
    fclose(wav_file_vol_decr);

    wav_header_printing(wh);

	return 0;
}

void wav_header_printing(struct wav_header wh){
    
    printf("ChunkID:%c%c%c%c\n", wh.ChunkID[0], wh.ChunkID[1], wh.ChunkID[2], wh.ChunkID[3]);
    printf("ChunkSize:%d\n", wh.ChunkSize);
    printf("Format:%c%c%c%c\n", wh.Format[0], wh.Format[1], wh.Format[2], wh.Format[3]);

    printf("Subchunk1ID:%c%c%c\n", wh.Subchunk1ID[0], wh.Subchunk1ID[1], wh.Subchunk1ID[2]);
    printf("Subchunk1Size:%d\n", wh.Subchunk1Size);
    printf("AudioFormat:%d\n", wh.AudioFormat);
    printf("NumChannel:%d\n", wh.NumChannel);
    printf("SampleRate:%d\n", wh.SampleRate);
    printf("ByteRate:%d\n", wh.ByteRate);
    printf("BlockAlign:%d\n", wh.BlockAlign);
    printf("BitsPerSample:%d\n", wh.BitsPerSample);

    printf("Subchunk2ID:%c%c%c%c\n", wh.Subchunk2ID[0], wh.Subchunk2ID[1], wh.Subchunk2ID[2], wh.Subchunk2ID[3]);
    printf("Subchunk2Size:%d\n", wh.Subchunk2Size);

    return 0;
}

