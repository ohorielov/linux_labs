#include <stdio.h>
#include "wav.h"

int main(int argc, char** argv) {
    wav* music = load_wav(argv[1]);

    wav_dump(music);

    free_wav(music);
}
