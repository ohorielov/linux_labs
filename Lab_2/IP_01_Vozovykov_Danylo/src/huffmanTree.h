#ifndef HUFFMAN_TREE
#define HUFFMAN_TREE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include "binaryTree.h"
#include "priorityQueue.h"

#ifndef MAX_CHARS
#define MAX_CHARS 256
#endif

TreeNode* buildTree(int freq[MAX_CHARS]);

#endif
