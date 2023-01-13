

#include "wav_header.h"

void load_wav(const char*, wav_header*, int16_t**);
void write_wav(const char*, wav_header*, int16_t*);
void adjust_wav(wav_header*, int16_t*, float);
void structure_wav(wav_header*);
