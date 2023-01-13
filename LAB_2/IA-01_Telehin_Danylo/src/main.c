#include "huffman.h"

#define INPUT_FILE "../non_compressed_text.txt"
#define COMPRESSED_FILE "../compressed_text.txt"
#define DECOMPRESSED_FILE "../decompressed.txt"

int main() {

    FILE* in = fopen(INPUT_FILE, "rb");
    FILE* out = fopen(COMPRESSED_FILE, "wb");

    encode(in,out); // encoding the file

    fclose(out);

    FILE* comp = fopen(COMPRESSED_FILE, "rb");
    FILE* decom = fopen(DECOMPRESSED_FILE, "w+b");

    decode(comp,decom);  // decoding the file

    fclose(comp);

    int ch1, ch2;
    while ((ch1 = fgetc(in)) == (ch2 = fgetc(decom)))  // comparing files
        if (ch1 == EOF) break;

    fclose(in);
    fclose(decom);
	
    if(ch1 == ch2){                                   // print the result of comparing
	printf("The input and output files are the same");
    }else{
     printf("The input and output files are NOT the same");
    }

    return 0;
}