#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct __attribute__((packed,aligned(4))){
uint32_t chunkID;
uint32_t chunkSize;
void* data;
}sub_chunk ;


typedef enum{
	MULTIPLY,
	ADD,
	TREMBLE
}work_mode;

void say(const char*);
char update_data(work_mode, sub_chunk*);
char read_wav(const char*);
float count_amp(float*, int, int, int);
