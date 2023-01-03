#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "huffman.h"

int main() {
    FILE *f = fopen("non_compressed_text.txt", "r");
    FILE *encoded_f = fopen("encoded.txt", "w+");
    FILE *new_decoded_f = fopen("decoded.txt", "w");
    assert(f != NULL);
    assert(encoded_f != NULL);
    assert(new_decoded_f != NULL);

    struct nodes_queue *q = build_queue(f);
    struct huffman_node *root = build_huffman_tree(q);
    struct character_table *tab = new_table();
    build_character_table(root, "", tab);

    huffman_encode(f, encoded_f, tab);
    huffman_decode(encoded_f, new_decoded_f, tab);

    free_tree(root);
    free(q);
    free_character_table(tab);
    
    fclose(f);
    fclose(encoded_f);
    fclose(new_decoded_f);
    return 0;
}
