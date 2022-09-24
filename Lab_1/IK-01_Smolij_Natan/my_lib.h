#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct
{
uint32_t chunkID;
uint32_t chunkSize;
void* data;
}sub_chunk;

void say(const char*);
char update_data(char,sub_chunk*);
char read_wav(const char*);
