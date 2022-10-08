#ifndef LAB1_H
#define LAB1_H
#include <stdio.h>
#define HEADER_SIZE 44


typedef struct header_struct wav_header;

FILE* read_wav_file(char* name);
FILE* write_edited_data(char* fileName, FILE* oldWav, float changeValue);

#endif
