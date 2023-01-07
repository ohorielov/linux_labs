#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// Number of bytes in .wav header
const int HEADER_SIZE = 44;
int main(int argc, char *argv[])
{
    FILE *input = fopen("input.wav", "r");
    FILE *output = fopen("output.wav", "w");
    float change = 2.0;
    uint8_t headerbuffer[HEADER_SIZE];
    fread(headerbuffer, sizeof(uint8_t), HEADER_SIZE, input);
    fwrite(headerbuffer, sizeof(uint8_t), HEADER_SIZE, output);
    uint16_t buffer;
    while(fread(&buffer, sizeof(uint16_t), 1, input)){
        buffer *= change;
        fwrite(&buffer, sizeof(uint16_t), 1, output);
    }
    fclose(input);
    fclose(output);
    return 0;
}
