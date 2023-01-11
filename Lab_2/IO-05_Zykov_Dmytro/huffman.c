#include "huffman.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

#include "pqueue.h"

#define MAX_TREE_HT 50
#define MAX_CHAR 256
#define FREQ_TABLE_SIZE (MAX_CHAR * sizeof(uint16_t))
#define BYTE 8

#define CHECK_BIT(var, pos) ((var) & (1 << (pos)))

// Global code table
uint32_t g_code_arr[MAX_TREE_HT];
uint8_t g_codetable[MAX_CHAR][MAX_TREE_HT + 1] = {0};

// Builds Huffman tree
struct pqueue_node *build_tree(const uint16_t *freq)
{
    struct pqueue *queue = pqueue_create(MAX_CHAR);
    if (queue == NULL) {
        fprintf(stderr, "Error creating pqueue");
    }

    int size = 0;
    for (int i = 0; i < MAX_CHAR; ++i) {
        if (freq[i] > 0) {
            queue->array[size++] = pqueue_node_create(i, freq[i]);
            if (queue->array[size - 1] == NULL) {
                fprintf(stderr, "Error creating pqueue_node");
            }
        }
    }
    queue->size = size;

    for (int i = pqueue_parent(queue->size - 1); i >= 0; --i) {
        pqueue_heapify(queue, i);
    }


    struct pqueue_node *left, *right, *top;
    while (queue->size > 1) {
        left = pqueue_pop(queue);
        right = pqueue_pop(queue);

        top = pqueue_node_create('$', left->freq + right->freq);
        top->left = left;
        top->right = right;

        pqueue_push(queue, top);
    }

    return pqueue_pop(queue);
}

void add_code_to_table(int item, int top)
{
    for (int i = 0; i < top; ++i) {
        g_codetable[item][i] = g_code_arr[i] ? '1' : '0';
    }
    g_codetable[item][top] = '\0';
}

void build_codetable(struct pqueue_node *node, int top)
{
    if (node->left) {
        g_code_arr[top] = 0;
        build_codetable(node->left, top + 1);
    }

    if (node->right) {
        g_code_arr[top] = 1;
        build_codetable(node->right, top + 1);
    }

    if (PQUEUE_NODE_IS_LEAF(node)) {
        add_code_to_table(node->item, top);
    }
}

// writes to a file bit by bit
ssize_t bitout(int fd, char bit, int *nbits, int *current_byte, int *nbytes)
{
    *current_byte <<= 1;
    *current_byte |= (bit == '1') ? 1 : 0;
    (*nbits)++;

    ssize_t rc = 0;
    if (*nbits == 8) {
        rc = write(fd, current_byte, 1);
        (*nbytes)++;
        *nbits = 0;
        *current_byte = 0;
    }

    return rc;
}

int huffman_encode(int input_fd, int output_fd)
{
    uint16_t freq[MAX_CHAR] = { 0 };

    char c;
    ssize_t rc = 0;
    while ((rc = read(input_fd, &c, 1)) == 1) {
        if (rc == -1) {
            fprintf(stderr, "Error reading input file");
            return 0;
        }
        freq[(int)c]++; // filling the frequency table
    }
    lseek(input_fd, 0, SEEK_SET);

    struct pqueue_node *root = build_tree(freq);

    ssize_t size = lseek(input_fd, 0, SEEK_END);
    uint8_t *buffer = (uint8_t *)malloc(size);
    if (buffer == NULL) {
        fprintf(stderr, "Error allocating buffer for input file");
        return 0;
    }
    lseek(input_fd, 0, SEEK_SET);
    rc = read(input_fd, buffer, size);
    if (rc != size) {
        fprintf(stderr, "Error reading input file");
        return 0;
    }

    // write frequency table to a file
    rc = write(output_fd, freq, FREQ_TABLE_SIZE);
    if (rc != FREQ_TABLE_SIZE) {
        fprintf(stderr, "Error writing frequency table");
        return 0;
    }

    build_codetable(root, 0);

    int nbits = 0, current_byte = 0, nbytes = 0;
    for (ssize_t i = 0; i < size; ++i)
    {
        int x = 0;
        while ((c = g_codetable[(int)buffer[i]][x++]) != '\0') {
            rc = bitout(output_fd, c, &nbits, &current_byte, &nbytes);
            if (rc == -1) {
                fprintf(stderr, "Error writing encoded data");
                return 0;
            }
        }
    }

    // write the left out byte
    int offset = 0;
    if (nbits != 0) {
        offset = 8 - nbits;
        current_byte <<= offset;
        rc = write(output_fd, &current_byte, 1);
    }
    rc = write(output_fd, &offset, 1);
    if (rc == -1) {
        fprintf(stderr, "Error writing encoded data");
        return 0;
    }
    
    free(buffer);
    return 1;
}

int huffman_decode(int input_fd, int output_fd)
{
    uint16_t freq[MAX_CHAR] = { 0 };
    ssize_t rc = read(input_fd, freq, FREQ_TABLE_SIZE);
    if (rc == -1) {
        fprintf(stderr, "Error reading input file");
        return 0;
    }

    ssize_t size = lseek(input_fd, -1, SEEK_END) - FREQ_TABLE_SIZE;
    uint8_t offset;
    rc = read(input_fd, &offset, 1);
    if (rc == -1) {
        fprintf(stderr, "Error reading input file");
        return 0;
    }
    lseek(input_fd, FREQ_TABLE_SIZE, SEEK_SET);
    uint8_t *buffer = (uint8_t *)malloc(size);
    if (buffer == NULL) {
        fprintf(stderr, "Error allocating buffer for input file");
        return 0;
    }
    
    rc = read(input_fd, buffer, size);
    if (rc == -1) {
        fprintf(stderr, "Error reading input file");
        return 0;
    }

    struct pqueue_node *root = build_tree(freq);
    if (root == NULL) {
        fprintf(stderr, "Error building Huffman tree");
        return 0;
    }

    build_codetable(root, 0);

    struct pqueue_node *current = root;
    uint8_t c, bits, item;
    ssize_t i, j;
    for (i = 0; i < size; ++i) {
        c = buffer[i];
        bits = BYTE;
        if (i == size - 1) {
            bits -= offset;
        }
        for (j = 0; j < bits; ++j) {
            if (CHECK_BIT(c, BYTE - 1)) {
                current = current->right;
            } else {
                current = current->left;
            }
            c <<= 1;

            if (PQUEUE_NODE_IS_LEAF(current)) {
                item = current->item;
                current = root;
                rc = write(output_fd, &item, 1);
                if (rc == -1) {
                    fprintf(stderr, "Error writing decoded data");
                    return 0;
                }
            }
        }
    }

    free(buffer);
    return 1;
}