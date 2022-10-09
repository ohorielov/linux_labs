#ifndef WAV_PROCESSOR_H
#define WAV_PROCESSOR_H

#include "wav_header.h"

#define ERROR 1
#define SUCCESS 0

int16_t* read_wav(const char* file, wav_header* wav);

void process_data(wav_header* wav, int16_t* data, int volume);

int write_data(const char* file, wav_header* wav, int16_t* data);

#endif