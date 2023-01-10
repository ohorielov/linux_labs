#ifndef HUFFMAN_ENCODER
#define HUFFMAN_ENCODER

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include "binaryTree.h"
#include "priorityQueue.h"
#include "huffmanTree.h"

void compress(FILE* inputFile, FILE* outputFile);

#endif
