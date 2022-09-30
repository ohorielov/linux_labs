#ifndef LAB_1_WAV_READER_H_
#define LAB_1_WAV_READER_H_

#include <stdint.h>

// WAV header chunks sizes
#define RIFF_SIZE   12
#define FMT_SIZE    24
#define DATA_SIZE   8

// "RIFF" chuck descriptor
typedef struct {
    uint32_t id;
    uint32_t size;
    uint32_t format;
} riff_t;

// "fmt" sub-chunk
typedef struct {
    uint32_t id;
    uint32_t size;
    uint16_t audio_format;
    uint16_t channels;
    uint32_t sample_rate;
    uint32_t byte_rate;
    uint16_t block_align;
    uint16_t bit_depth;
} fmt_t;

// "data" sub-chunk
typedef struct {
    uint32_t id;
    uint32_t size;
} data_t;

// WAV structure
typedef struct  {
    riff_t  riff;
    fmt_t   fmt;
    data_t  data;
} wav_t;


#endif // LAB_1_WAV_READER_H_
