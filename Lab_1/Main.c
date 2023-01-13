
#include <stdlib.h>
#include "WAV_HEADER.h"
int main (int argc, char *argv[]) {
    struct WAV_HEADER header;
    short *audio_data;
    read_wav_file( filename: "input.wav", &header, &audio_data);
    int data_size = header. data_size;
    decrease_volune (audio_data, data_size,
    factor: 0);
    write_wav_file( filename: "input. wav", header, audio_data, data_size);
    free( ptr: audio_data);
    return 0;
    }

