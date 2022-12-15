#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>

#ifndef WAV_LAB
#define WAV_LAB
#endif 

const int HEADER_SIZE = 44;
typedef int8_t BYTE;
typedef uint16_t BYTE2;
typedef int32_t BYTE4;

typedef struct{
    BYTE4 ChunkID;
    BYTE4 ChunkSize;
    BYTE4 Format;
    BYTE4 Subchunk1ID;
    BYTE4 Subchunk1Size;
    BYTE2 AudioFormat;
    BYTE2 NumChannels;
    BYTE4 SampleRate;
    BYTE4 ByteRate;
    BYTE2 BlockAlign;
    BYTE2 BitsPerSample;
    BYTE4 Subchunk2ID;
    BYTE4 Subchunk2Size;
    BYTE Data;
} Wav;