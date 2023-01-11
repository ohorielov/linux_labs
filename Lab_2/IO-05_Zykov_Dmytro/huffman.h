#ifndef HUFFMAN_H
#define HUFFMAN_H

#include <stddef.h>
#include <stdint.h>

#define HUFFMAN_SUCCESS 1
#define HUFFMAN_FAILURE 0

// Encodes file and writes the result
// Returns HUFFMAN_SUCCESS if successful
// and HUFFMAN_FAILURE otherwise
int huffman_encode(int input_fd, int output_fd);

// Decodes file and writes the result
// Returns HUFFMAN_SUCCESS if successful
// and HUFFMAN_FAILURE otherwise
int huffman_decode(int input_fd, int output_fd);

#endif // HUFFMAN_H