#define _CRT_SECURE_NO_WARNINGS



#include <stdio.h>
#include <fstream>

#define output "../output.wav"
#define input "..//Master Of Puppets.wav"
#define value  0.75

struct header {
    _int32 chunkID;
    _int32 ChunkSize;
    _int32 Format;
    _int32 Subchunk1ID;
    _int32 Subchunk1Size;
    _int16 AudioFormat;
    _int16 NumChannels;
    _int32 SampleRate;
    _int32 ByteRate;
    _int16 ByteAlign;
    _int16 BitsPerSample;
    _int32 Subchunk2ID;
    _int32 Subchunk2Size;
    _int8* Data;

    void read_data() {
        FILE* fp;
        fp = fopen(input, "r");
        if (fp == NULL) {
            printf("Cannot open file");
            exit(-1);
        }


        fread(&this->chunkID, 4, 1, fp);
        fread(&this->ChunkSize, 4, 1, fp);
        fread(&this->Format, 4, 1, fp);
        fread(&this->Subchunk1ID, 4, 1, fp);
        fread(&this->Subchunk1Size, 4, 1, fp);
        fread(&this->AudioFormat, 2, 1, fp);
        fread(&this->NumChannels, 2, 1, fp);
        fread(&this->SampleRate, 4, 1, fp);
        fread(&this->ByteRate, 4, 1, fp);
        fread(&this->ByteAlign, 2, 1, fp);
        fread(&this->BitsPerSample, 2, 1, fp);
        fread(&this->Subchunk2ID, 4, 1, fp);
        fread(&this->Subchunk2Size, 4, 1, fp);
        this->Data = (_int8*)malloc(this->Subchunk2Size);
        fread(this->Data, this->Subchunk2Size, 1, fp);
        fclose(fp);
    }

    void print_data() {
        printf("id: %c%c%c%c\n",
            ((char*)(&this->chunkID))[0],
            ((char*)(&this->chunkID))[1],
            ((char*)(&this->chunkID))[2],
            ((char*)(&this->chunkID))[3]);
        printf("ChunkSize: %u\n", this->ChunkSize);
        printf("Format: %u\n", this->Format);
        printf("Subchunk1ID: %u\n", this->Subchunk1ID);
        printf("Subchunk1Size: %u\n", this->Subchunk1Size);
        printf("AudioFormat: %u\n", this->AudioFormat);
        printf("NumChannels: %u\n", this->NumChannels);
        printf("SampleRate: %u\n", this->SampleRate);
        printf("ByteRate: %u\n", this->ByteRate);
        printf("ByteAlign: %u\n", this->ByteAlign);
        printf("BitsPerSample: %u\n", this->BitsPerSample);
        printf("Subchunk2ID: %u\n", this->Subchunk2ID);
        printf("Subchunk2Size: %u\n", this->Subchunk2Size);
        printf("DATA");
        printf("%d\n", ((uint16_t*)this->Data)[0]);

    }


    void change_and_safe() {

        int chunck_i = this->Subchunk2Size / sizeof(int16_t);

        FILE* out = fopen(output, "w");
        if (out == NULL) {
            printf("Cannot open file");
            exit(-1);
        }
        fwrite(&this->chunkID, 4, 1, out);
        fwrite(&this->ChunkSize, 4, 1, out);
        fwrite(&this->Format, 4, 1, out);
        fwrite(&this->Subchunk1ID, 4, 1, out);
        fwrite(&this->Subchunk1Size, 4, 1, out);
        fwrite(&this->AudioFormat, 2, 1, out);
        fwrite(&this->NumChannels, 2, 1, out);
        fwrite(&this->SampleRate, 4, 1, out);
        fwrite(&this->ByteRate, 4, 1, out);
        fwrite(&this->ByteAlign, 2, 1, out);
        fwrite(&this->BitsPerSample, 2, 1, out);
        fwrite(&this->Subchunk2ID, 4, 1, out);
        fwrite(&this->Subchunk2Size, 4, 1, out);



        for (_int32 i = 0; i < chunck_i; i++) {
            int16_t chunck = this->Data[i];
            chunck *= value;
            this->Data[i] = chunck;

        }

        fwrite(this->Data, this->Subchunk2Size, 1, out);
        fclose(out);
    }

};
