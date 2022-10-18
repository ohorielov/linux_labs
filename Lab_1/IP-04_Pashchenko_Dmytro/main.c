#include "wav.h"

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

int32_t main() {
    struct wav* music = open_wav("/Users/mrpaschenko/Developer/linux_labs/Lab_1/IP-04_Pashchenko_Dmytro/Master Of Puppets.wav");

    change_volume(music, 5, false);
    create_new_wav(music, "/Users/mrpaschenko/Developer/linux_labs/Lab_1/IP-04_Pashchenko_Dmytro/Master Of Puppets (new).wav");

    free(music);

    return 0;
}