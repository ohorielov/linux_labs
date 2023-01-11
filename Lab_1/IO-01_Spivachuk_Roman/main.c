#include <stdio.h>
#include <stdlib.h>
#include "lab1sp.h"

int main(int argc, char** argv) {
    if (argc != 4) {
        printf("Wrong parameter count. Usage: %s File_from_read File_to_write Multiply_value\n", *argv);
        exit(1);
    }

    FILE* oldWav = read_wav_file(*(argv + 1));
    float change_value = atof(*(argv + 3));
    FILE* newWav = write_edited_data(*(argv + 2), oldWav, change_value);

    fclose(oldWav);
    fclose(newWav);
    exit(0);
}
