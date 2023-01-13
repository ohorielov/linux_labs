#include <stdint.h>
#include <string.h>

struct WavHeader {
      uint8_t chunkID[4];
      uint32_t chunkSize;
      uint8_t format[4];
      uint8_t subchunk1ID[4];
      uint32_t subchunk1Size;
      uint16_t audioFormat;
      uint16_t numChannels;
      uint32_t sampleRate;
      uint32_t byteRate;
      uint16_t blockAlign;
      uint16_t bitsPerSample;
      uint8_t subchunk2ID[4];
      uint32_t subchunk2Size;
      uint16_t* data;
    };
    int read(const char *filename, struct WavHeader *wav);
    void edit(double a, struct WavHeader *wav);
    void print(const char *filename, struct WavHeader *wav);
    int write(const char *filename, struct WavHeader *wav);


