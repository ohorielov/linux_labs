#include <stdint-gcc.h>

unsigned int convert2(const unsigned char *arr);
unsigned int convert4(const unsigned char *arr);
struct WavHeader convertHeader(struct WavHeaderInBytes headerInBytes);
void proceedHeader(uint8_t *header, long headerLength);
short proceedFile();