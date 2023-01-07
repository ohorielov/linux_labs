#include <stdio.h>
#include "wav.h"

int main(int argc, char** argv) {
    if(argc != 4) {
        printf("Usage: %s <input.wav> <output.wav> <modifier>\n", argv[0]);
        return -1;
    }

    wav* music = load_wav(argv[1]);

    wav_dump(music);

    printf("%d\n", ((uint16_t*)music->_data.data)[0]);

    wav_db_add(music, atof(argv[3]));

    wav_save(music, argv[2]);

    printf("%d\n", ((uint16_t*)music->_data.data)[0]);

    free_wav(music);
}
