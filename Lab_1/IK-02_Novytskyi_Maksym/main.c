#include "wav_processor.h"

#define VOLUME_PERCENT 0.5

int main() {
    struct Wav_header wav = {};

    read_wav("../Master Of Puppets.wav", &wav);

    volume_change(VOLUME_PERCENT, &wav);

    write_wav("Output.wav", &wav);

    return 0;
}