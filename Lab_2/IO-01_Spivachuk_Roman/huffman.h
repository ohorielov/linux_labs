#ifndef HUFFMAN_H
#define HUFFMAN_H

#include <stdio.h>
#define MAXNODES 100 // max nodes in a queue
#define MAXCODELEN 20 // max length of encoded character's code

struct huffman_node {
    char data;
    unsigned int freq;
    struct huffman_node *left, *right;
};

struct nodes_queue {
    unsigned int length;
    struct huffman_node *nodes[MAXNODES];
};

struct encoded_character {
    char original_char;
    char code[MAXCODELEN];
};

struct character_table {
    unsigned int length;
    struct encoded_character *table[MAXNODES];
};

// create new node for a huffman tree
struct huffman_node *new_node(char data, unsigned int freq);
// create queue of nodes
struct nodes_queue *new_prior_queue();
// create new pair character : code
struct encoded_character *new_char(char original_char, char *code);
// create data structure for character pairs
struct character_table *new_table();

// append new node to a queue
void append_node(struct nodes_queue *queue, struct huffman_node *node);
// append new character to character table
void append_to_table(struct character_table *t, struct encoded_character *c);

// simulating priorities in a queue
struct huffman_node *find_min_node(struct nodes_queue *q);
// remove node from a queue
void queue_remove_node(struct nodes_queue *queue, struct huffman_node *node);

// create new queue from input stream and fill it with characters and their frequencies
struct nodes_queue *build_queue(FILE *input_stream);
// build huffman tree and return root
struct huffman_node *build_huffman_tree(struct nodes_queue *queue);
// build character table from huffman tree
void build_character_table(struct huffman_node *root, char *code, struct character_table *t);

// find code of char c in t
char *find_code(struct character_table *t, char c);
// find char by code in t
char find_char(struct character_table *t, char* code);
// encode source file into dest using ctable
void huffman_encode(FILE *source, FILE *dest, struct character_table *ctable);
// decode source file into dest using ctable
void huffman_decode(FILE *source, FILE *dest, struct character_table *ctable);

void free_tree(struct huffman_node *root);
void free_character_table(struct character_table *t);

#endif // HUFFMAN_H
