#include "huffman.h"

#include <stdio.h>
#include <stdlib.h>

#define MAX_TREE_HT 50
#define BYTE 8

#define CHECK_BIT(var, pos) ((var) & (1 << (pos)))

typedef struct mh_node
{
    char c;
    int freq;
    struct mh_node *left, *right;
} mh_node_t;

typedef struct 
{
    int size;
    int capacity;
    mh_node_t **array;
} minheap_t;

mh_node_t *new_mh_node(char c, int freq)
{
    mh_node_t *node = (mh_node_t *) malloc(sizeof(mh_node_t));
    node->c = c;
    node->freq = freq;
    node->left = node->right = NULL;
    return node;
}

minheap_t *minheap_create(int capacity)
{
    minheap_t *mh = (minheap_t *) malloc(sizeof(minheap_t));
    mh->array = (mh_node_t **) malloc(sizeof(mh_node_t *) * capacity);
    mh->size = 0;
    mh->capacity = capacity;
    return mh;
}

void mh_node_delete(mh_node_t *node)
{
    if (!node) return;
    mh_node_delete(node->left);
    mh_node_delete(node->right);
    free(node);
}

void minheap_heapify(minheap_t *mh, size_t idx)
{
    size_t left = 2 * idx + 1;
    size_t right = 2 * idx + 2;
    size_t smallest = idx;

    if (left < mh->size && mh->array[left]->freq < mh->array[smallest]->freq) {
        smallest = left;
    }

    if (right < mh->size && mh->array[right]->freq < mh->array[smallest]->freq) {
        smallest = right;
    }

    if (smallest != idx) {
        minheap_swap(&mh->array[smallest], &mh->array[idx]);
        minheap_heapify(mh, smallest);
    }
}

mh_node_t *minheap_extract(minheap_t *mh)
{
    mh_node_t *node = mh->array[0];
    mh->array[0] = mh->array[mh->size - 1];

    --mh->size;
    minheap_heapify(mh, 0);

    return node;
}

void minheap_insert(minheap_t *mh, mh_node_t *node)
{
    ++mh->size;
    int i = mh->size - 1;
    while (i && node->freq < mh->array[(i - 1) / 2]->freq) {
        mh->array[i] = mh->array[(i - 1) / 2];
        i = (i - 1) / 2;
    }
    mh->array[i] = node;
}

void minheap_free(minheap_t *mh)
{
    for (size_t i = 0; i < mh->size; ++i) {
        mh_node_delete(mh->array[i]);
    }
    free(mh->array);
    free(mh);
}

void minheap_swap(mh_node_t **a, mh_node_t **b)
{
    mh_node_t *t = *a;
    *a = *b;
    *b = t;
}

int arr[MAX_TREE_HT];
char codes[MAX_ASCII][MAX_TREE_HT + 1] = {0};

// Builds Huffman tree
mh_node_t *build_tree(const int freq[MAX_ASCII])
{
    minheap_t *mh = minheap_create(MAX_ASCII);

    int size = 0;
    for (int i = 0; i < MAX_ASCII; ++i) {
        if (freq[i] > 0) {
            mh->array[size++] = new_mh_node(i, freq[i]);
        }
    }
    mh->size = size;

    for (int i = ((mh->size - 1) - 1) / 2; i >= 0; --i) {
        minheap_heapify(mh, i);
    }

    mh_node_t *left, *right, *top;
    while (mh->size > 1) {
        left = minheap_extract(mh);
        right = minheap_extract(mh);

        top = new_mh_node('$', left->freq + right->freq);
        top->left = left;
        top->right = right;

        minheap_insert(mh, top);
    }

    return minheap_extract(mh);
}

void calculate_codes(mh_node_t *node, int top)
{
    if (node->left) {
        arr[top] = 0;
        calculate_codes(node->left, top + 1);
    }

    if (node->right) {
        arr[top] = 1;
        calculate_codes(node->right, top + 1);
    }

    if (node->left == NULL && node->right == NULL) {
        for (int i = 0; i < top; ++i) {
            codes[node->c][i] = arr[i] ? '1' : '0';
        }
        codes[node->c][top] = '\0';
    }
}

int bitout(int fd, char bit, int *nbits, int *current_byte, int *nbytes)
{
    *current_byte <<= 1;
    *current_byte |= (bit == '1') ? 1 : 0;
    (*nbits)++;

    int rc = 0;
    if (*nbits == 8) {
        rc = write(fd, current_byte, 1);
        (*nbytes)++;
        *nbits = 0;
        *current_byte = 0;
    }

    return rc;
}

int compress(const char* src, char dst[], int dst_size, int freq[MAX_ASCII]) {
    int size = strlen(src);
    for (int i = 0; i < size; ++i) {
        freq[(int)src[i]]++;
    }

    mh_node_t *root = build_tree(freq);
    calculate_codes(root, 0);
    
    int bits = 0, bytes = 0;
    char byte = 0;
    for (int i = 0; i < size; i++) {
        int code_size = strlen(codes[(int)src[i]]);
        for (int j = 0; j < code_size; j++) {
            byte = byte << 1;
            byte |= codes[(int)src[i]][j] == '1' ? 1 : 0;
            bits++;
            if (bits == 8) {
                if (bytes == dst_size) {
                    return;
                }
                dst[bytes++] = byte;
                bits = 0;
                byte = 0;
            }
        }
    }

    int offset = 0;
    if (bits > 0) {
        offset = 8 - bits;
        byte = byte << offset;
        if (bytes == dst_size)
            return 
        dst[bytes] = byte;
    }
    
    dst[bytes] = '\0';

    return offset;
}

void decompress(const char* src, char* dst, int dst_size, int offset, int freq[MAX_ASCII])
{
    mh_node_t *root = build_tree(freq);
    calculate_codes(root, 0);

    mh_node_t *node = root;
    int size = strlen(src);
    int written = 0;
    for (int i = 0; i < size; i++) {
        char c = src[i];
        int bits = 8;
        if (i == size - 1) {
            bits -= offset;
        }

        for (int j = 0; j < bits; j++) {
            if (c & (1 << 7)) {
                node = node->right;
            } else {
                node = node->left;
            }
            c = c << 1;

            if (node->left == NULL && node->right == NULL) {
                dst[written++] = node->c;
                node = root;
            }
        }
    }
}