#include "huff.h"

#define non_compressed_file "./non_compressed_text.txt"
#define compressed_file "./compressed_text.txt"
#define decompressed_file "./decompressed_text.txt"

int cmp_output() {
    FILE *fp1 = fopen(non_compressed_file,  "rb");
    FILE *fp2 = fopen(decompressed_file, "rb");

    char *buffer_1;
    char *buffer_2;
    long filelen_1;
    long filelen_2;

    fseek(fp1, 0, SEEK_END); 
    filelen_1 = ftell(fp1);
    rewind(fp1);

    buffer_1 = (char *)malloc(filelen_1 * sizeof(char));
    fread(buffer_1, filelen_1, 1, fp1);
    fclose(fp1);

    fseek(fp2, 0, SEEK_END);
    filelen_2 = ftell(fp2); 
    rewind(fp2); 

    buffer_2 = (char *)malloc(filelen_2 * sizeof(char)); 
    fread(buffer_2, filelen_2, 1, fp2);
    fclose(fp2);

    if (filelen_1 != filelen_2) return 0;

    if(memcmp(buffer_1, buffer_2, filelen_1) == 0) 
        return 1;
    return 0;
}

int main(int args, char *argv[]) {
    compress(non_compressed_file, compressed_file);
    decompress(compressed_file, decompressed_file);

    if (cmp_output() == 1)
        printf("equal\n");
    else 
        printf("not equal\n");
}
