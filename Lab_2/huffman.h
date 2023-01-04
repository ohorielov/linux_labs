#ifndef HUFFMAN_H
#define HUFFMAN_H

#define MAX_ASCII 256

int compress(const char* src, char* dst, int dst_size, int freq[MAX_ASCII]);

void decompress(const char* src, char* dst, int dst_size, int offset, int freq[MAX_ASCII]);

#endif // HUFFMAN_H