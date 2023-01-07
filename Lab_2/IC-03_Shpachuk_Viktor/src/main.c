#include "huffman.h"

#define INPUT_FILE "../non_compressed_text.txt"
#define COMPRESSED_FILE "../compressed_text.txt"
#define DECOMPRESSED_FILE "../decompressed.txt"


int compareFiles(const char* file1, const char* file2) {
    FILE* fp1 = fopen(file1, "rb");
    FILE* fp2 = fopen(file2, "rb");

    int ch1, ch2;
    while ((ch1 = fgetc(fp1)) == (ch2 = fgetc(fp2)))
        if (ch1 == EOF) break;

    fclose(fp1);
    fclose(fp2);

    return (ch1 == ch2) ? 0 : -1;
}

int fileProcess(
    const char *inputFile, const char *outputFile, 
    int (*huffman_func)(FILE*, FILE*)) {

    FILE* in = fopen(inputFile, "rb");
    FILE* out = fopen(outputFile, "wb");

    huffman_func(in, out);

    fclose(out);
    fclose(in);

    return 0;
}

int main() {
    fileProcess(INPUT_FILE, COMPRESSED_FILE, encode);
    fileProcess(COMPRESSED_FILE, DECOMPRESSED_FILE, decode);

    if (compareFiles(INPUT_FILE, DECOMPRESSED_FILE) == 0)
        printf("Files are identical!\n");
    else
        printf("Files are different!\n");

    return 0;
}
