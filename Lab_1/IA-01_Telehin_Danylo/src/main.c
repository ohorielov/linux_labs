#include "wav_edit.h"

#define VOLUME 0.2

#define input "../Master Of Puppets.wav"
#define output "../Master Of Puppets(edited).wav"

int main(int args, char* argv[]) {
    struct WavHeader wav_header = {};

    FILE *file_input = fopen(input, "rb");
    read_wav(file_input, &wav_header);

	printf(&wav_header);

    change_volume(&wav_header, VOLUME);

    FILE* file_output = fopen(output, "wb");
    write_wav(file_output, &wav_header);

    return 0;
}