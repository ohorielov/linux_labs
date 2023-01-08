#include <stdio.h>
#include <stdlib.h>


struct RiffChunk {
    char chunk_id[4];
    int chunk_size;
    char format[4];
};

struct FmtSubchunk {
    char subchunk1_id[4];
    int subchunk1_size; 
    short audio_format; 
    short num_channels;
    int sample_rate;
    int byte_rate; 
    short block_align; 
    short bits_per_sample;     
};

struct DataSubchunk {
    char subchunk2_id[4]; 
    int subchunk2_size; 
    short *data;
};

struct WavHeader {
    struct RiffChunk riff;
    struct FmtSubchunk fmt;
    struct DataSubchunk data;
};

void read_wav(FILE* file, struct WavHeader* wh);
void write_wav(FILE *file, struct WavHeader *wh);
void change_volume(struct WavHeader *wh, float scale);
