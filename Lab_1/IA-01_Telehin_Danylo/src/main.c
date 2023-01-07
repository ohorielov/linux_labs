#include "wav_edit.h"

#define VOLUME_FACTOR 0.5

#define input "../Master Of Puppets.wav"
#define output "../Master Of Puppets CHANGED VOLUME.wav"

int main(int args, char* argv[]) {
    struct WavHeader wav_header;

    FILE *file_input = fopen(input, "rb");
    read_wav(file_input, &wav_header);

    change_volume(&wav_header, VOLUME_FACTOR);

    FILE* file_output = fopen(output, "wb");
    write_wav(file_output, &wav_header);

    return 0;
}