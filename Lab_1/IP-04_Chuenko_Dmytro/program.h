#include <iostream>
#include <stdio.h>
#include <fstream>

#define outputpath "../newaudio.wav"
#define audiopath "..//Master Of Puppets.wav"
#define defvalue 0.75

class Program
{
public:
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
    _int8 *Data;

public:
    void Read()
    {
        FILE *fp;
        fp = fopen(audiopath, "r");
        if (fp == NULL)
        {
            printf("Cannot open file");
            exit(-1);
        }
        else
        {
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
            this->Data = (_int8 *)malloc(this->Subchunk2Size);
            fread(this->Data, this->Subchunk2Size, 1, fp);
        }

        fclose(fp);
    }

    void Output()
    {
        std::cout << "id: %c%c%c%c\n"
                  << ((char *)(&this->chunkID))[0] << ((char *)(&this->chunkID))[1] << ((char *)(&this->chunkID))[2] << ((char *)(&this->chunkID))[3];

        std::cout << "ChunkSize: %u\n"
                  << this->ChunkSize;
        std::cout << "Format: %u\n"
                  << this->Format;
        std::cout << "Subchunk1ID: %u\n"
                  << this->Subchunk1ID;
        std::cout << "Subchunk1Size: %u\n"
                  << this->Subchunk1Size;
        std::cout << "AudioFormat: %u\n"
                  << this->AudioFormat;
        std::cout << "NumChannels: %u\n"
                  << this->NumChannels;
        std::cout << "SampleRate: %u\n"
                  << this->SampleRate;
        std::cout << "ByteRate: %u\n"
                  << this->ByteRate;
        std::cout << "ByteAlign: %u\n"
                  << this->ByteAlign;
        std::cout << "BitsPerSample: %u\n"
                  << this->BitsPerSample;
        std::cout << "Subchunk2ID: %u\n"
                  << this->Subchunk2ID;
        std::cout << "Subchunk2Size: %u\n"
                  << this->Subchunk2Size;
        std::cout << "Data: %d\n"
                  << ((uint16_t *)this->Data)[0];
    }

    void Update()
    {

        int chunck_i = this->Subchunk2Size / sizeof(int16_t);

        FILE *out = fopen(outputpath, "w");
        if (out == NULL)
        {
            printf("Cannot open file");
            exit(-1);
        }
        else
        {
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

            for (_int32 i = 0; i < chunck_i; i++)
            {
                int16_t chunck = this->Data[i];
                chunck *= defvalue;
                this->Data[i] = chunck;
            }

            fwrite(this->Data, this->Subchunk2Size, 1, out);
            fclose(out);
        }
    }

    void Algorithm()
    {
        Read();
        Output();
        Update();
    }
};