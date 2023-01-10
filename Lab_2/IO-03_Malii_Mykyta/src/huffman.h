#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#ifndef LINUX_LABS_HUFFMAN_H
#define LINUX_LABS_HUFFMAN_H
#define FREQUENCY_SIZE 128
#define FILENAME_SIZE 64

typedef struct Node_struct {
    int frequency;
    char symbol;
    struct Node_struct *left, *right;

} *Node;

FILE *encoding(unsigned int *frequency, char filename[FILENAME_SIZE], FILE *fp_in, FILE *fp_out);

FILE *open_file(FILE *fp_in, char filename[FILENAME_SIZE], int argc, char *argv[]);

FILE *create_table(FILE *fp_out, char filename[FILENAME_SIZE], unsigned int *frequency);

FILE *file_for_decode(FILE *fp_in, char filename[FILENAME_SIZE], char *mode);

Node create_node(int frequency, char symbol, Node a, Node b);

Node remove_in_queue();

void print_table(unsigned int *frequency);

void insert_into_queue(Node node);

void assign_code(Node node, char *symbol, int len);

void read_file(FILE *fp_in, unsigned int *frequency);

void calculate_bytes(unsigned int *frequency);

void clear_data(char filename[FILENAME_SIZE], unsigned int *frequency);

void read_table(FILE *fp_table, unsigned int *frequency);

void decoding(FILE *fp_encode, FILE *fp_out, char filename[FILENAME_SIZE]);

void calculate_bytes_after_decoding(unsigned int *frequency);

#endif //LINUX_LABS_HUFFMAN_H
