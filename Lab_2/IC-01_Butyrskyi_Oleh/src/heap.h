#include "huffman.h"

typedef struct heap {
    Hnode**hNodes;
    int size;
    int top;
} heap;

Hnode* heapHead(heap);
void initializeHeap(heap*);
void heapPush(heap*, Hnode*);
void heapPop(heap*);
int heapSize(heap);
void heapDestroy(heap*);
