#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <malloc.h>
#include <stdbool.h>
#include <fcntl.h>

#define HEADER_SIZE 44
#define SOUND_BYTE_MAX INT8_MAX
#define SOUND_BYTE_MIN INT8_MIN

typedef int8_t soundByte;
typedef const uint8_t* string;

typedef struct WAV_RIFF {
    uint8_t ChunkID[4];
    uint32_t ChunkSize;
    uint8_t Format[4];
} RIFF_t;

typedef struct WAV_FMT {
    uint8_t Subchunk1ID[4];
    uint32_t Subchunk1Size;
    uint16_t AudioFormat;
    uint16_t NumChannels;
    uint32_t SampleRate;
    uint32_t ByteRate;
    uint16_t BlockAlign;
    uint16_t BitsPerSample;
} FMT_t;

typedef struct WAV_data {
    uint8_t Subchunk2ID[4];
    uint32_t Subchunk2Size;
    soundByte *AudioData;
} Data_t;

typedef struct WAV_file {
    RIFF_t Riff;
    FMT_t Fmt;
    Data_t Data;
} Wav;

Wav* read_wav(string path);

void make_wav_volume_down(Wav *wav, uint8_t scaleValue);

uint32_t write_wav(Wav* wav, string path);

void print_wav_header(Wav *wav);
