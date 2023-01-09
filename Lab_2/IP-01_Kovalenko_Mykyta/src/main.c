#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "huffman.h"

#define FAILURE 1
#define SUCCESS 0

void print_help() {
      printf("USAGE: ./huffman [encode | decode | roundtrip] <input file> <output file> [<round trip file>]\n");
}

int main(int argc, char **argv) {
    init();

    if (strcmp(argv[1], "encode") == 0 && argc == 4) {
        if (encode(argv[2], argv[3]) != 0)
            return FAILURE;
    }
    else if (strcmp(argv[1], "decode") == 0 && argc == 4) {
        if (decode(argv[2], argv[3]) != 0)
            return FAILURE;
    }
    else if (strcmp(argv[1], "roundtrip") == 0 && argc == 5) {
        if (assert_round_trip(argv[2], argv[3], argv[4]) != 0)
            return FAILURE;

        printf("Round trip successful!\n");
    }
    else {
        print_help();
    }

    finalise();
    return SUCCESS;
}
