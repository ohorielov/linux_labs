#ifndef LINUX_LABS_WAV_H
#define LINUX_LABS_WAV_H

    #include <stdint.h>
    #include <stdbool.h>

    struct riffChunk {
        uint8_t chunkId[4];
        uint32_t chunkSize;
        uint8_t format[4];
    };

    struct fmtSubchunk {
        uint8_t subchunk1Id[4];
        uint32_t subchunk1Size;
        uint16_t audioFormat;
        uint16_t numChannels;
        uint32_t sampleRate;
        uint32_t byteRate;
        uint16_t blockAlign;
        uint16_t bitsPerSample;
    };

    struct dataSubchunk {
        uint8_t subchunk2Id[4];
        uint32_t subchunk2Size;
        int8_t *wavData;
    };

    struct wav {
        struct riffChunk riff;
        struct fmtSubchunk fmt;
        struct dataSubchunk data;
    };

    struct wav* open_wav(const char* fileName);

    void change_volume(struct wav* someWav, char changeValue, bool isIncrease);

    void create_new_wav(struct wav* someWav, const char* fileName);

#endif
