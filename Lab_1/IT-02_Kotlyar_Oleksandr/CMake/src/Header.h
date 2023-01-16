
#pragma pack(push,1)
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>


typedef struct WAV_RIFF
{
    char ChunkID[4];
    uint32_t ChunkSize;
    char Format[4];
}  RIFF;

typedef struct WAV_FMT
{
    char Subchunk1ID[4];
    uint32_t Subchunk1Size;
    uint16_t AudioFormat;
    uint16_t NumChannels;
    uint32_t SampleRate;
    uint32_t ByteRate;
    uint16_t BlockAlign;
    uint16_t BitsPerSample;
} FMT;


typedef struct WAV_data
{
    char Subchunk2ID[4];
    uint32_t Subchunk2Size;
    uint16_t* _data;
} Data;


typedef struct WAV_fotmat
{
    RIFF riff;
    FMT fmt;
    Data data;
} Wav;
#pragma pack(pop)