#include "wav.h"

#include <stdlib.h>
#include <stdbool.h>

int main() {
    struct wav* file = open_wav("/Users/mrpaschenko/Developer/linux_labs/Lab_1/IP-04_Pashchenko_Dmytro/Master Of Puppets.wav");

    change_volume(file, 5, false);
    create_new_wav(file, "/Users/mrpaschenko/Developer/linux_labs/Lab_1/IP-04_Pashchenko_Dmytro/Master Of Puppets (new).wav");

    free(file);

    return 0;
}