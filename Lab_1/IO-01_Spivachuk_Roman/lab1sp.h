#ifndef LAB1_H
#define LAB1_H
#include <stdio.h>
#define HEADER_SIZE 44
#define FOUR_BYTES_FIELD 4
#define SIZE_OF_CHUNK 2
#define NUM_OF_CHUNKS 1

typedef struct header_struct wav_header;

FILE* read_wav_file(char* name);
FILE* write_edited_data(char* fileName, FILE* oldWav, float changeValue);

#endif

