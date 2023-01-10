#include "huff.h"

#define CHARACTER_LIMIT 256

void check_final_byte(FILE *compressed, int *byte_index, int *cur_byte, long int *huff_structure_size) {
    if (*byte_index != 0) {
        int check = fputc(*cur_byte, compressed);

        if (check == EOF) return;

        (*huff_structure_size)++;
        *cur_byte = 0;
    }
}

void compress(const char *non_compressed_name, const char *compressed_name) {
    int char_frequency[CHARACTER_LIMIT] = {0}; 
    long uncompressed_size;

    FILE *uncompressed = fopen(non_compressed_name, "r");

    uncompressed_size = count_char_frequency(uncompressed, char_frequency);
    fseek(uncompressed, 0, SEEK_SET);

    ListNode *head = init_sorted_list(char_frequency);
    TreeNode *root = build_tree(head);

    char **table = build_table(root);
    FILE *compressed = fopen(compressed_name, "w+");

    int byte_index = 0;
    int cur_byte = 0;
    long huff_structure_size = 0;

    fwrite(&huff_structure_size, sizeof(long), 1, compressed);
    fwrite(&uncompressed_size, sizeof(long), 1, compressed);

    write_huffman_binary_structure(root, compressed, &cur_byte, &byte_index, &huff_structure_size);
    check_final_byte(compressed, &byte_index, &cur_byte, &huff_structure_size);
    
    write_encoded_characters(table, uncompressed, compressed);

    fseek(compressed, 0, SEEK_SET);
    fwrite(&huff_structure_size, sizeof(long), 1, compressed);

    delete_table(table);
    delete_tree(root);

    fclose(compressed);
    fclose(uncompressed);
}

void decompress(const char *compressed_name, const char *decompressed_name) {
    FILE *compressed = fopen(compressed_name, "r");
    
    long huff_structure_size; 
    long uncompressed_size;
    
    if (fread(&huff_structure_size, sizeof(long), 1, compressed) != 1) return;
    if (fread(&uncompressed_size, sizeof(long), 1, compressed) != 1) return;

    int current_byte = fgetc(compressed); 
    int byte_index = 0;

    TreeNode *huffman_root = build_tree_from_compressed(compressed, &current_byte, &byte_index);
    FILE *restore = fopen(decompressed_name, "w");

    decompress_(huffman_root, compressed, restore, uncompressed_size);

    delete_tree(huffman_root);
    
    fclose(compressed);
    fclose(restore);
}
