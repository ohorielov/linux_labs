#include <stdio.h>
#include <stdlib.h>
//A file container format for storing data in tagged chunks
struct RiffChunk {
    char ChunkId[4];
    int ChunkSize;
    char Format[4];
};
//Describes the format of the sound information in the data sub-chunk
struct FmtSubchunk {
    char Subchunk1Id[4];
    int Subchunk1Size; 
    short AudioFormat; 
    short NumChannels;
    int SampleRate;
    int ByteRate; 
    short BlockAlign; 
    short BitsPerSample;     
};
//Indicates the size of the sound information and contains the raw sound data
struct DataSubchunk {
    char Subchunk2Id[4]; 
    int Subchunk2Size; 
    short *data;
};

struct WavHeader {
    struct RiffChunk riff;
    struct FmtSubchunk fmt;
    struct DataSubchunk data;
};

void read(FILE* file, struct WavHeader* wh);
void write(FILE *file, struct WavHeader *wh);
void print(struct WavHeader *wav_h);
void volumechange(struct WavHeader *wh, float scale);