#include <stdio.h>
#include <stdlib.h>
#include <sys/fcntl.h>
#include <stdint.h>

#define WAV_HEADER_SIZE_BYTES 44


struct Wav {
    uint32_t riff_header;
    uint32_t wav_size;
    uint8_t wave_header;

    uint32_t fmt_header;
    uint32_t chunk_size;
    uint16_t audio_format;
    uint16_t num_channels;
    uint32_t sample_rate;
    uint32_t byte_rate;
    uint16_t sample_alignment;
    uint16_t bit_depth;

    uint32_t data_header;
    uint32_t size_bytes;
    int16_t *data;
};

void parse_wav(int filedesc, struct Wav* wh);

void write_wav(const char *file_name, struct Wav *wh);

void change_volume(struct Wav *wh, float scale);

void print_wav_header(struct Wav *wh);
