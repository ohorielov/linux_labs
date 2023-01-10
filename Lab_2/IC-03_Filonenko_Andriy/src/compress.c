#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "huffman_tree.h"
#include "list.h"
#include "compress.h"
#define CHARACTER_LIMIT 256

long count_char_frequency(FILE *in, int *frequency) {
    int current_character = fgetc(in);
    long file_size_bytes = 0; 

    if (current_character == EOF) return EXIT_SUCCESS;

    while (current_character != EOF) {
        frequency[current_character]++;
        file_size_bytes++;
        current_character = fgetc(in);
    }

    return file_size_bytes;
}


TreeNode *build_tree(ListNode *head) {
    if (head == NULL) return NULL;

    ListNode *buffer_node = NULL;

    while (head->next != NULL) {
        ListNode *new_node = malloc(sizeof(ListNode));
        new_node->parent = malloc(sizeof(TreeNode));

        if (new_node == NULL)
            return NULL;

        
        new_node->parent->right = head->next->parent;
        new_node->parent->left = head->parent;
        new_node->char_frequency = head->char_frequency + head->next->char_frequency;
        new_node->parent->value = -1;
        new_node->next = NULL;

        if (head->next->next == NULL) buffer_node = new_node;
        else buffer_node = head->next->next;
        
        free(head->next);
        free(head);

        head = buffer_node;
        head = add_element_sorted(head, new_node);
    }
    TreeNode *returnRootNode = head->parent;
    
    free(head);
    return returnRootNode;
}

char **build_table(TreeNode *root) {
    char **table = malloc(sizeof(char *) * CHARACTER_LIMIT); 
    char encoded_character[500] = {'\0'}; 
    int index = 0; 

    build_table_(root, encoded_character, '\0', table, 0, &index);

    return table;
}


void build_table_(TreeNode *root, char *encoded_character, char character_to_add, char **table, int encoded_length, int *index) {
    if (root == NULL) return;

    encoded_character[*index] = character_to_add;

    if (encoded_length != 0)
        (*index)++;

    if (node_is_leaf(root)) {
        table[root->value] = malloc((sizeof(char) * encoded_length) + 1);
        
        if (table[root->value] == NULL) return;

        strcpy(table[root->value], encoded_character);

        if (encoded_length >= 1)
            encoded_character[encoded_length - 1] = '\0';

        (*index)--;

        return;
    }

    build_table_(root->left, encoded_character, '0', table, encoded_length + 1, index);
    build_table_(root->right, encoded_character, '1', table, encoded_length + 1, index);

    if (encoded_length >= 1)
        encoded_character[encoded_length - 1] = '\0';

    (*index)--;
}


void write_encoded_characters(char **table, FILE *in, FILE *out) {
    int current_char_file;
    int byte_index = 0; 
    int current_byte = 0;
    int string_index = 0;
    
    do {        
        current_char_file = fgetc(in);

        if (current_char_file == -1) break;

        while (1) {
            if(byte_index == 8) {
                int check = fputc(current_byte, out);
                
                if(check == EOF) return;

                current_byte = 0;
                byte_index = 0;
            }

            char current_character = table[current_char_file][string_index];

            if (current_character == '\0') {
                string_index = 0;
                break;
            }

            if (current_character == '0') {
                byte_index++; 
            } else if (current_character == '1') {
                current_byte = add_one_to_byte(byte_index, current_byte);
                byte_index++;
            } else {
                return;
            }

            string_index++;
        }
    } while (current_char_file != EOF);

    if (byte_index != 0) {
        int check = fputc(current_byte, out);
        if(check == EOF) return;
    }
}

int add_one_to_byte(int byte_index, int current_byte) {
    int mask =  (0xFF >> 7) << byte_index;
    current_byte = current_byte | mask;
    
    return current_byte;
}

void write_huffman_binary_structure(TreeNode *root, FILE *out, int *current_byte, int *byte_index, long *structure_size) {
    if (root == NULL) return;
    
    if(node_is_leaf(root)) {
        *current_byte = add_one_to_byte(*byte_index, *current_byte);
        (*byte_index)++;

        if (*byte_index > 7) {
            if (fputc(*current_byte, out) == EOF) return;

            (*structure_size)++;
            *byte_index = 0;
            *current_byte = 0;
        }

        *current_byte = add_character_to_byte(out, *current_byte, byte_index, root->value);

        if (*current_byte == EOF) return;

        (*structure_size)++;
    } else {
        (*byte_index)++;

        if (*byte_index > 7) {
            int check = fputc(*current_byte, out);

            if (check == EOF) return;

            (*structure_size)++;
            *byte_index = 0;
            *current_byte = 0;
        }
    }
    
    write_huffman_binary_structure(root->left, out, current_byte, byte_index, structure_size);
    write_huffman_binary_structure(root->right, out, current_byte, byte_index, structure_size);
}

int add_character_to_byte(FILE *out, int current_byte, int *byte_index, int character) {
    int mask = character << *byte_index;
    current_byte = current_byte | mask;
    int left_over_bits = *byte_index;

    int check = fputc(current_byte, out);

    if (check == EOF) return EOF;

    *byte_index =  0;
    current_byte = 0;

    if (left_over_bits == 0) return current_byte;
    
    mask = character >> (8 - left_over_bits);
    current_byte = current_byte | mask;
    *byte_index += left_over_bits;

    return current_byte;
}

void delete_table(char **table) {
    for (int i = 0; i < CHARACTER_LIMIT; i++)
        if (table[i] != NULL)
            free(table[i]);

    free(table);
}
