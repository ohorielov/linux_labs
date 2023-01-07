
#ifndef HEADER_HUFF
#define HEADER_HUFF

#define huffman_symbols_limit 256

#define input_text "./non_compressed_text.txt"
#define compressed_text "./compressed_text.txt"

typedef struct Hnode {
    unsigned char symbol;
    int entries;
    struct Hnode* left;
    struct Hnode* right;
} Hnode;

typedef struct HuffEncoder{
    unsigned long long codeWords[huffman_symbols_limit];
    unsigned long long lengths[huffman_symbols_limit];
} HuffEncoder;

Hnode* newHnode(char, int);
void encoderInitialize(HuffEncoder*, int [], int);

#endif
