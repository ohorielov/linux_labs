#ifndef WAV_H
#define WAV_H

#include <stdint.h>

#define WAV_INFO(MSG, MEMBER) (printf("%s %d\n", (MSG), (wav->_ ## MEMBER)))

typedef struct {
    // RIFF
    uint32_t _chunkID;
    uint32_t _chunkSize;
    uint8_t _Format[4];

    // fmt
    uint32_t _Subchunk1ID;
    uint32_t _Subchunk1Size;
    uint16_t _AudioFormat;
    uint16_t _NumChannels;
    uint32_t _SampleRate;
    uint32_t _ByteRate;
    uint16_t _BlockAlign;
    uint16_t _BitsPerSample;

    // data
    uint32_t _Subchunk2ID;
    uint32_t _Subchunk2Size;
    int16_t *_Data;
} __attribute__ ((__packed__)) Wav;

Wav *WavOpen(const char *path);

void WavWrite(Wav *wav, const char *path);

void WavSetVolume(Wav *wav, float volume);

void WavFree(Wav *wav);

#endif
