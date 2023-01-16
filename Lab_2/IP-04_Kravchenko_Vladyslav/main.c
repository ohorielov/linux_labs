#include <string.h>
#include "huffman.h"
#include "simple_file_buffer.h"

#define INPUT_LOCATION "..//non_compressed_text.txt"
#define ENCODED_FILE_LOCATION "./encoded.txt"
#define DECODED_FILE_LOCATION "./decoded.txt"

int file_encode(const char *input_file, const char *output_file) {
    struct buffer_ops *in, *out;

    in = create_file_buffer_ops(input_file, "rb");
    if (!in) {
        LOGE("Create input file ops failed\n");
        return 1;
    }
    out = create_file_buffer_ops(output_file, "wb");
    if (!out) {
        LOGE("Create input file ops failed\n");
        goto OUT;
    }
    encode(in, out);
    desotry_file_buffer_ops(out);
OUT:
    desotry_file_buffer_ops(in);
    return 0;
}

int file_decode(const char *input_file, const char *output_file) {
    struct buffer_ops *in, *out;

    in = create_file_buffer_ops(input_file, "rb");
    if (!in) {
        LOGE("Create input file ops failed\n");
        return 1;
    }
    out = create_file_buffer_ops(output_file, "wb");
    if (!out) {
        LOGE("Create input file ops failed\n");
        goto OUT;
    }
    decode(in, out);
    desotry_file_buffer_ops(out);
OUT:
    desotry_file_buffer_ops(in);
    return 0;
}

int are_identical_files(const char* location_1, const char* location_2) {
    FILE *fp1 = fopen(location_1, "rb");
    FILE *fp2 = fopen(location_2, "rb");
    for (unsigned long pos = 0; ; pos++) {
        int c1 = getc(fp1);
        int c2 = getc(fp2);
        if (c1 == EOF || c2 == EOF) {
            if (c1 != c2)
                return -1;
            else
                break;
        }
        if (c1 != c2) 
            return 0;
    }
    return 1;
}

void main(int argc, char *argv[]) {
    file_encode(INPUT_LOCATION, ENCODED_FILE_LOCATION);

    file_decode(ENCODED_FILE_LOCATION, DECODED_FILE_LOCATION);

    printf(
        are_identical_files(INPUT_LOCATION, DECODED_FILE_LOCATION) ?
        "Iitial and compressed-decompressed files are identical\n" :
        "Program fucked up, files are not identical\n"
    );
}
