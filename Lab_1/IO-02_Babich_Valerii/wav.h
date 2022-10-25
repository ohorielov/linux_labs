#ifndef WAV_HANDLE
#define WAV_HANDLE

#include <stdint.h>
#include <stdbool.h>



struct wavDataHeader {
    uint8_t sunchunk2Id[4];
    uint32_t subchunk2Size;
    int8_t *wavData;
};

struct wavRIFF {
    uint8_t chunkId[4];
    uint32_t chunkSize;
    uint8_t format[4];
};

struct wavFmt {
    uint8_t subchunk1Id[4];
    uint32_t sunchunk1Size;
    uint16_t audioFormat;
    uint16_t numChannels;
    uint32_t sampleRate;
    uint32_t byteRate;
    uint16_t blockAlign;
    uint16_t bitsPerSample;
};

struct wav {
    struct wavRIFF riff;
    struct wavFmt fmt;
    struct wavDataHeader dataHeader;
};

struct wav* wav_open(const uint8_t* file); 

void create_wav(struct wav* wav, const uint8_t* file); 

void change_volume(struct wav* wav, int8_t value, bool isIncrease);



#endif