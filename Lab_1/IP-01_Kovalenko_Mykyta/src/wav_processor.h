#include "wav_header.h"

void load_wav(const char*, wav_header*);
void write_wav(const char*, wav_header*);
void strengthen_wav(wav_header*, float);
void dump_wav(wav_header*);
