#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "huffman_tree.h"
#include "list.h"
#include "decompress.h"
#define CHARACTER_LIMIT 256

TreeNode *build_tree_from_compressed(FILE *in, int *current_byte, int *byte_index) {
    if (*byte_index >= 8) {
        *current_byte = fgetc(in);
        *byte_index = 0;
    }

    int mask = 0xFF >> 7 << *byte_index;
    int current_bit = (mask & *current_byte) >> *byte_index;

    (*byte_index)++;
    TreeNode *parent = NULL;

    if (current_bit == 0) {
        parent = malloc(sizeof(TreeNode));
        parent->left = NULL;
        parent->right = NULL;
        parent->value = 0;
    } else if (current_bit == 1) {
        parent = malloc(sizeof(TreeNode));
        parent->left = NULL;
        parent->right = NULL;
        parent->value = get_character_as_bytes(in, current_byte, byte_index);
        return parent;
    }

    parent->left = build_tree_from_compressed(in, current_byte, byte_index);
    parent->right = build_tree_from_compressed(in, current_byte, byte_index);

    return parent;
}

int get_character_as_bytes(FILE *in, int *current_byte, int *read_byte_index) {
    if (*read_byte_index % 8 == 0) {
        int result = fgetc(in);
        *current_byte = fgetc(in);
        *read_byte_index = 0;
        return result;
    }

    int next_byte = fgetc(in);
    int result = 0;
    int write_byte_index = 0;
    int mask;

    while (write_byte_index < 8) {
        mask = 0XFF >> 7 << (*read_byte_index % 8);
        mask = mask & *current_byte;
        mask = mask >> (*read_byte_index % 8);

        result = result | (mask << write_byte_index);
        (*read_byte_index)++;
        write_byte_index++;

        if (*read_byte_index == 8)
            *current_byte = next_byte;
    }
    *read_byte_index = *read_byte_index % 8;

    return result;
}

void decompress_(TreeNode *root_node, FILE *input, FILE *output, long uncompressed_size) {
    long read_bytes = 0;
    int byte_index = 0;
    TreeNode *traverse = root_node;
    int current_byte = fgetc(input);

    while (read_bytes < uncompressed_size) {
        if (node_is_leaf(traverse)) {
            fputc(traverse->value, output);
            traverse = root_node;
            read_bytes++;
            
            continue;
        }

        if (byte_index >= 8) {
            current_byte = fgetc(input);
            byte_index = 0;
        }
        
        int mask = 0xFF >> 7 << byte_index;
        int current_bit = (mask & current_byte) >> byte_index;
        byte_index++;

        if (current_bit == 0) traverse = traverse->left;
        else if (current_bit == 1) traverse = traverse->right;
        else return;
    }
}
