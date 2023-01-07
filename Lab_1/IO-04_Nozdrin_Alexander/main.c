#include "wav_processing.h"

#define VOLUME_SCALE 0.5

int main() {
    struct Wav_header wav = {};

    read_wav_file("../Master Of Puppets.wav", &wav);
    
    edit_volume(VOLUME_SCALE, &wav);
    
    write_wav_file("Output.wav", &wav);

    return 0;
}

