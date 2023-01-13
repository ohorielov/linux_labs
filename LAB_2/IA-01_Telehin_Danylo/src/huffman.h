#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILL_WITH_ZEROES(x, length) (memset(x, 0, length))

#define TABLE_LENGTH 256


struct FileHeader {
    uint32_t tableSize;
    uint64_t fileSize;
};

struct HuffmanCode {
    uint8_t code[TABLE_LENGTH];
    uint8_t length;
};

struct Node {
    struct Node *top;
    struct Node *left;
    struct Node *right;

    uint64_t weight;
    uint8_t value;
};

int encode(FILE *in, FILE *out);
int decode(FILE *in, FILE *out);