#include "huffman.h"
#include "utils.h"


uint8_t setByte(uint8_t a, uint8_t b) {
    return a |= (1 << b);
}

uint8_t getByte(uint8_t a, uint8_t b) {
    return a & (1 << b);
}

int firstGTSecond(const void* a, const void* b) {
    if (*(uint64_t*)a > *(uint64_t*)b)
        return 1;
    return -1;
}

struct Node * makeHuffmanTree(uint64_t* table, int size) {
    int firstUnused = 0;

    struct Node* huffmanNodes = malloc(TABLE_LENGTH * 2 * sizeof(struct Node));
    struct Node* tree[TABLE_LENGTH];

    FILL_WITH_ZEROES(huffmanNodes, TABLE_LENGTH * 2 * sizeof(struct Node));

    for (int i = 0; i < size; i++) {
        tree[i] = &huffmanNodes[firstUnused++];
        tree[i]->value = table[i] & 0xff;
        tree[i]->weight = table[i] >> 8;
    }

    for (int i = 0; i < size - 1; i++) {
        struct Node* node = &huffmanNodes[firstUnused++];

        node->weight = tree[i]->weight + tree[i + 1]->weight;
        node->left = tree[i];
        node->right = tree[i + 1];
        
        tree[i] = NULL;
        tree[i + 1] = node;
    }
    tree[size - 1]->top = huffmanNodes;

    return tree[size - 1];
}

void generateHuffmanCode(struct HuffmanCode* codeList, struct Node* tree, char* code, int len) {
    if (!tree->left) {
        memcpy(codeList[tree->value].code, code, len);
        codeList[tree->value].length = len;
        return;
    }

    generateHuffmanCode(codeList, tree->left, code, len + 1);
    code[len] = 1;
    generateHuffmanCode(codeList, tree->right, code, len + 1);
    code[len] = 0;
}

void freeHuffmanTree(struct Node* tree) {
    if (tree->top != NULL)
        free(tree->top);
}

void fillTable(FILE* in, uint64_t table[TABLE_LENGTH]) {
    int current4Bytes;
    while(!feof(in)) {
        fileRead(in, &current4Bytes, 1);
        table[current4Bytes]++;
    }
    rewind(in);

    for (int i = 0; i < TABLE_LENGTH; i++) {
        table[i] = i | (table[i] << 8);
    }
    qsort(table, TABLE_LENGTH, sizeof(uint64_t), firstGTSecond);
}

void moveBufferToNonZero(uint64_t table[TABLE_LENGTH], int* current4Bytes) {
    for (*current4Bytes = 0; *current4Bytes < TABLE_LENGTH; *current4Bytes++) {
        if (table[*current4Bytes] >> 8) {
            break;
        }
    }

    if (*current4Bytes > TABLE_LENGTH - 2) {
        *current4Bytes = TABLE_LENGTH - 2;
    }
}

int encode(FILE* in, FILE* out) {
    struct HuffmanCode codeList[TABLE_LENGTH];
    struct Node* tree = NULL;
    struct FileHeader fileHeader;
    uint64_t table[TABLE_LENGTH] = {0};

    fillTable(in, table);

    int current4Bytes;
    moveBufferToNonZero(table, &current4Bytes);

    tree = makeHuffmanTree(table + current4Bytes, TABLE_LENGTH - current4Bytes);

    FILL_WITH_ZEROES(codeList, TABLE_LENGTH);
    char code[TABLE_LENGTH] = { 0 };
    generateHuffmanCode(codeList, tree, code, 0);

    FILL_WITH_ZEROES(&fileHeader, sizeof(fileHeader));
    fileHeader.fileSize = tree->weight;
    fileHeader.tableSize = TABLE_LENGTH - current4Bytes;

    fwrite(&fileHeader, 1, sizeof(struct FileHeader), out);
    fwrite(table + current4Bytes, 1, (TABLE_LENGTH - current4Bytes) * sizeof(uint64_t), out);

    uint8_t bufferByte = 0;
    uint8_t usedBits = 0;
    while (!feof(in)) {
        fileRead(in, &current4Bytes, 1);
        for (int i = 0; i < codeList[current4Bytes].length; i++) {
            if (codeList[current4Bytes].code[i]) {
                bufferByte = setByte(bufferByte, 7 - usedBits);
            }

            usedBits++;

            if (usedBits == 8) {
                fwrite(&bufferByte, 1, 1, out);

                bufferByte = 0;
                usedBits = 0;
            }
        }
    }

    if (usedBits)  {
        fwrite(&bufferByte, 1, 1, out);
    }

    freeHuffmanTree(tree);

    return 0;
}

int decode(FILE* in, FILE* out) {
    struct FileHeader fh;
    uint64_t table[TABLE_LENGTH] = {0};

    fileRead(in, &fh, sizeof(fh));
    fileRead(in, table, sizeof(uint64_t) * fh.tableSize);

    struct Node* tree = makeHuffmanTree(table, fh.tableSize);
    struct Node* currentNode = tree;

    uint64_t size = 0;
    int bufferByte = 0;
    int usedBits = 0;
    while (size < fh.fileSize) {
        if (!usedBits) {
            if (feof(in)) return 1;
            fileRead(in, &bufferByte, 1);
        }

        if (getByte(bufferByte, 7 - usedBits)) {
            currentNode = currentNode->right;
        } else {
            currentNode = currentNode->left;
        }

        if (!currentNode->left) {
            fwrite(&currentNode->value, 1, 1, out);
            currentNode = tree;
            size++;
        }

        if (++usedBits == 8) {
            usedBits = 0;
        }
    }

    freeHuffmanTree(tree);
    
    return 0;
}
