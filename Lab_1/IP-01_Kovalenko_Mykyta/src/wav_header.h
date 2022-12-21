#ifndef WAV_HEADER_H_
#define WAV_HEADER_H_

#include "stdint.h"

typedef struct {
	uint32_t chunk_id;
	uint32_t chunk_size;
	uint32_t format;

	uint32_t subchunk1_id;
	uint32_t subchunk1_size;
	uint16_t audio_format;
	uint16_t num_channels;
	uint32_t sample_rate;
	uint32_t byte_rate;
	uint16_t block_align;
	uint16_t bits_per_sample;

	uint32_t subchunk2_id;
	uint32_t subchunk2_size;
} wav_header;

#endif
