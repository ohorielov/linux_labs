#include "wav.h"

int main(int argc, char** argv) {
    wav* file = read_wav(argv[1]);
    multiply_wav_db(file, 0.2);
    save_wav(file, argv[2]);

    return 0;
}
