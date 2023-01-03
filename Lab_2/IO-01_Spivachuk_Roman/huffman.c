#include <stdlib.h>
#include <string.h>
#include "huffman.h"

struct huffman_node *new_node(char data, unsigned int freq) {
    struct huffman_node *node = malloc(sizeof(struct huffman_node));
    node->data = data;
    node->freq = freq;
    node->left = node->right = NULL;
    return node;
}

struct nodes_queue *new_prior_queue() {
    struct nodes_queue *queue = malloc(sizeof(struct nodes_queue));
    queue->length = 0;
    return queue;
}

struct encoded_character *new_char(char original_char, char *code) {
    struct encoded_character *c = malloc(sizeof(struct encoded_character));
    c->original_char = original_char;
    strncpy(c->code, code, MAXCODELEN);
    return c;
}

struct character_table *new_table() {
    struct character_table *ct = malloc(sizeof(struct character_table));
    ct->length = 0;
    return ct;
}

void append_to_table(struct character_table *t, struct encoded_character *c) {
    t->table[t->length++] = c;
}

void append_node(struct nodes_queue *queue, struct huffman_node *node) {
    queue->nodes[queue->length++] = node;
}

struct huffman_node *find_min_node(struct nodes_queue *q) {
    struct huffman_node *min = q->nodes[0];
    for (int i = 0; i < q->length; i++) {
        if (q->nodes[i]->freq < min->freq)
            min = q->nodes[i];
    }
    return min;
}

struct nodes_queue *build_queue(FILE *input_stream) {
    struct nodes_queue *q = new_prior_queue();
    int c;
    char characters[255];
    int freq[255] = {0};
    while ((c = fgetc(input_stream)) != EOF) {
        characters[c] = (char)c;
        freq[c]++;
    }
    for (int i = 0; i < 255; i++) {
        if (freq[i] != 0) {
            struct huffman_node *n = new_node(characters[i], freq[i]);
            append_node(q, n);
        }
    }
    return q;
}

void queue_remove_node(struct nodes_queue *queue, struct huffman_node *node) {
    for (int i = 0; i < queue->length; i++) {
        if (queue->nodes[i] == node) {
            while (i < queue->length - 1) {
                queue->nodes[i] = queue->nodes[i + 1];
                i++;
            }
            break;
        }
    }
    queue->length--;
}

struct huffman_node *build_huffman_tree(struct nodes_queue *queue) {
    struct huffman_node *root;
    while (queue->length > 1) {
        // @ will be the service character, so we won't be able to encode/decode it
        root = new_node('@', 0);
        struct huffman_node *left_node = find_min_node(queue);
        root->left = left_node;
        queue_remove_node(queue, left_node);
        struct huffman_node *right_node = find_min_node(queue);
        root->right = right_node;
        queue_remove_node(queue, right_node);
        root->freq = root->left->freq + root->right->freq;
        append_node(queue, root);
    }
    return root;
}

void build_character_table(struct huffman_node *root, char *code, struct character_table *t) {
    if (root == NULL)
        return;
    if (root->data != '@')
        append_to_table(t, new_char(root->data, code));

    char left_code[MAXCODELEN];
    char right_code[MAXCODELEN];
    strcpy(left_code, code);
    strcat(left_code, "0");
    strcpy(right_code, code);
    strcat(right_code, "1");

    build_character_table(root->left, left_code, t);
    build_character_table(root->right, right_code, t);
}

void free_tree(struct huffman_node *root) {
    if (root == NULL)
        return;
    free_tree(root->left);
    free_tree(root->right);
    free(root);
}

void free_character_table(struct character_table *t) {
    for (int i = 0; i < t->length; i++)
        free(t->table[i]);
    free(t);
}

char *find_code(struct character_table *t, char c) {
    for (int i = 0; i < t->length; i++) {
        if (t->table[i]->original_char == c)
            return t->table[i]->code;
    }
    exit(-1);
}

char find_char(struct character_table *t, char* code) {
    for (int i = 0; i < t->length; i++) {
        if (strcmp(t->table[i]->code, code) == 0)
            return t->table[i]->original_char;
    }
    return '@';
}

void huffman_encode(FILE *source, FILE *dest, struct character_table *ctable) {
    rewind(source);
    int c;
    while ((c = getc(source)) != EOF) {
        fprintf(dest, "%s", find_code(ctable, (char)c));
    }
}

void huffman_decode(FILE *source, FILE *dest, struct character_table *ctable) {
    rewind(source);
    char current_code[MAXCODELEN] = "";
    int c;
    char found;
    while ((c = getc(source)) != EOF) {
        char current_digit[2] = {(char)c, '\0'};
        strcat(current_code, current_digit);
        if ((found = find_char(ctable, current_code)) != '@') {
            putc(found, dest);
            strcpy(current_code, "");
        }
    }
}