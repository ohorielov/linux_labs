#ifndef HUFFMAN_DECODER
#define HUFFMAN_DECODER

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include "binaryTree.h"
#include "priorityQueue.h"
#include "huffmanTree.h"

void decompress(FILE* inputFile, FILE* outputFile);

#endif
