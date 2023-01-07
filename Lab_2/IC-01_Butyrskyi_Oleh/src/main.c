#include <stdio.h>
#include <string.h>
#include "encoder_decoder.h"
#include <stdio.h>
#include <string.h>

#define BUFFER_SIZE 1024


int files_equal(const char* filename1, const char* filename2) {
    FILE* file1 = fopen(filename1, "rb");
    FILE* file2 = fopen(filename2, "rb");

    int result = 1;
    char buffer1[BUFFER_SIZE];
    char buffer2[BUFFER_SIZE];
    size_t bytesRead1, bytesRead2;

    do {
        bytesRead1 = fread(buffer1, 1, BUFFER_SIZE, file1);
        bytesRead2 = fread(buffer2, 1, BUFFER_SIZE, file2);
        if (bytesRead1 != bytesRead2 || memcmp(buffer1, buffer2, bytesRead1) != 0) {
            result = 0;
            break;
        }
    } while (bytesRead1 > 0 && bytesRead2 > 0);

    fclose(file1);
    fclose(file2);
    return result;
}

int main(int argc, char **argv) {
    compress(input_text);
    decompress(compressed_text);

    if (files_equal("./non_compressed_text.txt", "./decoded.txt")) {
        printf("non_compressed == decoded");
    } else {
        printf("non_compressed != decoded");
    }

    return 0;
}
