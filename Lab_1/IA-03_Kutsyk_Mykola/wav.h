#ifndef WAV_H
#define WAV_H

#include <stdint.h>

#pragma pack(push, 1)

// The WAV header struct
typedef struct {
  uint32_t chunk_id;         // RIFF chunk ID
  uint32_t chunk_size;       // RIFF chunk size
  uint32_t format;           // RIFF format
  uint32_t subchunk1_id;     // fmt subchunk ID
  uint32_t subchunk1_size;   // fmt subchunk size
  uint16_t audio_format;     // audio format (e.g. PCM, float)
  uint16_t num_channels;     // number of channels
  uint32_t sample_rate;      // sample rate
  uint32_t byte_rate;        // byte rate
  uint16_t block_align;      // block align
  uint16_t bits_per_sample;  // bits per sample
  uint32_t subchunk2_id;     // data subchunk ID
  uint32_t subchunk2_size;   // data subchunk size
} wav_header_t;

#pragma pack(pop)

#endif
