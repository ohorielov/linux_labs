#include <stdint.h>

struct riff_part {
    uint8_t riff_header[4];
    uint32_t file_size;
    uint8_t wave[4];
};

struct format_part {
    uint8_t fmt_header[4];
    uint32_t fmt_length;
    uint16_t format_tag;
    uint16_t channels;
    uint32_t sample_per_second;
    uint32_t byterate;
    uint16_t block_align;
    uint16_t bits_per_sample;
};

struct data_part {
    uint8_t data_header[4];
    uint32_t sample_data_length;
};

struct wav_header {
    struct riff_part riff;
    struct format_part fmt;
    struct data_part data;
};
