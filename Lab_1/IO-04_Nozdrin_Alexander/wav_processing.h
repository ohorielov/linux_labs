#include "stdint.h"

struct Wav_header {
    uint8_t chunk_id[4];
    uint32_t chunk_size;
    uint8_t format[4];

    uint8_t subchunk1_id[4];
    uint32_t subchunk1_size;
    uint16_t audio_format;
    uint16_t num_channels;
    uint32_t sample_rate;
    uint32_t byte_rate;
    uint16_t block_align;
    uint16_t bits_per_sample;

    uint8_t subchunk2_id[4];
    uint32_t subchunk2_size;
    uint16_t *data;
};


void edit_volume(float percent, struct Wav_header *wav);
void read_wav_file(const char *filename, struct Wav_header *wav);
void write_wav_file(const char *filename, struct Wav_header *wav);

