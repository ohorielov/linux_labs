#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "stdint.h"

#include "huffman.h"
#include "node_t.h"

#define MAX_BUFFER_SIZE 256
#define CHARACTERS_COUNT 256

#define FAILURE 1
#define SUCCESS 0

int active_count;
int *frequency;
uint32_t original_size;

node_t *nodes;
int nodes_count;
int *leaf_index;
int *parent_index;

uint8_t buffer[MAX_BUFFER_SIZE];
int bits_in_buffer = 0;
int current_bit = 0;

int eof_input;

int encode(const char* ifile, const char *ofile) {
    FILE *fin, *fout;

    if ((fin = fopen(ifile, "rb")) == NULL) {
        perror("Failed to open input file");
        return FAILURE;
    }

    if ((fout = fopen(ofile, "wb")) == NULL) {
        perror("Failed to open output file");
        fclose(fin);
        return FAILURE;
    }

    determine_frequency(fin);
    allocate_tree();

    add_leaves();
    write_header(fout);
    build_tree();
    fseek(fin, 0, SEEK_SET);

    int c;

    while ((c = fgetc(fin)) != EOF)
        encode_character(fout, c);

    flush_buffer(fout);
    fclose(fin);
    fclose(fout);

    return SUCCESS;
}

int decode(const char* ifile, const char *ofile) {
    FILE *fin, *fout;

    if ((fin = fopen(ifile, "rb")) == NULL) {
        perror("Failed to open input file");
        return FAILURE;
    }

    if ((fout = fopen(ofile, "wb")) == NULL) {
        perror("Failed to open output file");
        fclose(fin);
        return FAILURE;
    }

    if (read_header(fin) == 0) {
        build_tree();

        int i = 0, bit;
        int node_index = nodes[nodes_count].index;

        while (1) {
            bit = read_bit(fin);

            node_index = nodes[node_index * 2 - bit].index;

            if (node_index > 0)
                continue;

            char c = -node_index;
            fwrite(&c, 1, 1, fout);

            if (++i == original_size)
                break;

            node_index = nodes[nodes_count].index;
        }
    }

    fclose(fin);
    fclose(fout);

    return SUCCESS;
}

int assert_round_trip(const char* ifile, const char* ofile, const char* rtfile) {
    FILE *fin, *frt;
    int c1, c2, pos;

    encode(ifile, ofile);
    init();
    decode(ofile, rtfile);

    fin = fopen(ifile, "rb");
    frt = fopen(rtfile, "rb");

    for(pos = 0;; pos++) {
        c1 = getc(fin);
        c2 = getc(frt);

        if (c1 != c2) {
            printf("Round trip failed at position [%i]: different chars (%i) <-> (%i)\n", pos, c1, c2);
            return FAILURE;
        }

        if (c1 == EOF)
            break;
    }

    fclose(fin);
    fclose(frt);

    return SUCCESS;
}

void init() {
    active_count = 0;
    frequency = NULL;
    original_size = 0;

    nodes = NULL;
    nodes_count = 0;
    leaf_index = NULL;
    parent_index = NULL;

    frequency = calloc(2 * CHARACTERS_COUNT, sizeof(int));
    leaf_index = frequency + CHARACTERS_COUNT - 1;

    eof_input = 0;
}

void determine_frequency(FILE *f) {
    int c;

    while ((c = fgetc(f)) != EOF) {
        // count unique characters that are present in the text
        if (!frequency[c])
            active_count++;

        frequency[c]++;
        original_size++;
    }
}

void allocate_tree() {
    nodes = calloc(2 * active_count, sizeof(node_t));
    parent_index = calloc(active_count, sizeof(int));
}

int add_node(int index, int weight) {
    int i = nodes_count++;

    while (i >= 0 && nodes[i].weight > weight) {
        memcpy(&nodes[i + 1], &nodes[i], sizeof(node_t));

        if (nodes[i].index <= 0)
            leaf_index[-nodes[i].index]++;
        else
            parent_index[nodes[i].index]++;

        i--;
    }

    i++;
    nodes[i].index = index;
    nodes[i].weight = weight;

    if (index <= 0)
        leaf_index[-index] = i;
    else
        parent_index[index] = i;

    return i;
}

void add_leaves() {
    int i, freq;

    for (i = 0; i < CHARACTERS_COUNT; ++i) {
        freq = frequency[i];

        if (freq > 0)
            add_node(-i, freq);
    }
}

void build_tree() {
    int a, b, index, free_index = 1;

    while (free_index < nodes_count) {
        a = free_index++;
        b = free_index++;
        index = add_node(b / 2, nodes[a].weight + nodes[b].weight);
        parent_index[b / 2] = index;
    }
}

void encode_character(FILE *fout, int character) {
    int node_index = leaf_index[character];
    int stack_top = 0;
    int *stack = calloc(active_count, sizeof(int));

    while (node_index < nodes_count) {
        stack[stack_top++] = node_index % 2;
        node_index = parent_index[(node_index + 1) / 2];
    }

    while (--stack_top >= 0)
        write_bit(fout, stack[stack_top]);

    free(stack);
}

int write_bit(FILE *f, int bit) {
    // check if the buffer is full
    if (bits_in_buffer == MAX_BUFFER_SIZE * 8) {
        size_t bytes_written = fwrite(buffer, 1, MAX_BUFFER_SIZE, f);

        if (bytes_written < MAX_BUFFER_SIZE && ferror(f))
            return FAILURE;

        bits_in_buffer = 0;
        memset(buffer, 0, MAX_BUFFER_SIZE);
    }

    // otherwise pack the bit into the buffer
    if (bit)
        buffer[bits_in_buffer / 8] |= (1 << (7 - bits_in_buffer % 8));

    bits_in_buffer++;
    return SUCCESS;
}

int flush_buffer(FILE *f) {
    if (bits_in_buffer) {
        size_t bytes_written = fwrite(buffer, 1, (bits_in_buffer + 7) / 8, f);

        if (bytes_written < MAX_BUFFER_SIZE && ferror(f))
            return -1;

        bits_in_buffer = 0;
    }
    return SUCCESS;
}

int read_bit(FILE *f) {
    if (current_bit == bits_in_buffer) {
        if (eof_input)
            return EOF;

        size_t bytes_read = fread(buffer, 1, MAX_BUFFER_SIZE, f);

        if (bytes_read < MAX_BUFFER_SIZE) {
            if (feof(f))
                eof_input = 1;
        }

        bits_in_buffer = bytes_read * 8;
        current_bit = 0;
    }

    if (bits_in_buffer == 0)
        return EOF;

    int bit = (buffer[current_bit / 8] >> (7 - current_bit % 8)) & 1;
    ++current_bit;
    return bit;
}

void finalise() {
    free(parent_index);
    free(frequency);
    free(nodes);
}

int write_header(FILE *f) {
     int i, j, byte = 0;
     int size = sizeof(uint32_t) + 1 + active_count * (1 + sizeof(int));
     uint32_t weight;
     char *buffer = calloc(size, 1);

     if (buffer == NULL)
         return FAILURE;

     j = sizeof(int);

     while (j--)
         buffer[byte++] = (original_size >> (j * 8)) & 0xff;

     buffer[byte++] = active_count;

     for (i = 1; i <= active_count; ++i) {
         weight = nodes[i].weight;
         buffer[byte++] = -nodes[i].index;
         j = sizeof(int);

         while (j--)
             buffer[byte++] = (weight >> (j * 8)) & 0xff;
     }

     fwrite(buffer, 1, size, f);
     free(buffer);
     return SUCCESS;
}

int read_header(FILE *f) {
     int i, j, byte = 0;
     size_t bytes_read;
     uint8_t buff[4];

     bytes_read = fread(&buff, 1, sizeof(int), f);
     if (bytes_read < 1)
         return EOF;

     byte = 0;
     original_size = buff[byte++];

     while (byte < sizeof(int))
         original_size = (original_size << 8) | buff[byte++];

     bytes_read = fread(&active_count, 1, 1, f);

     if (bytes_read == 0)
         return EOF;

     allocate_tree();

     int size = active_count * (1 + sizeof(int));
     uint32_t weight;
     char *buffer = calloc(size, 1);

     if (buffer == NULL)
         return FAILURE;

     fread(buffer, 1, size, f);
     byte = 0;

     for (i = 1; i <= active_count; ++i) {
         nodes[i].index = -buffer[byte++];
         j = 0;
         weight = buffer[byte++];

         while (++j < sizeof(int))
             weight = (weight << 8) | (uint8_t)buffer[byte++];

         nodes[i].weight = weight;
     }

     nodes_count = active_count;
     free(buffer);
     return SUCCESS;
}
