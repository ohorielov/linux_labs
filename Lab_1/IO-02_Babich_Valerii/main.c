#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Number of bytes in .wav header
const int HEADER_SIZE = 44;

int main(int argc, char *argv[])
{
    printf("start");

    FILE *input = fopen("Master\ Of\ Puppets.wav", "r");
    FILE *output = fopen("output.wav", "w");

    float change = 2.0;

    uint8_t headerbuffer[44];
    fread(headerbuffer, sizeof(uint8_t), 44, input);
    fwrite(headerbuffer, sizeof(uint8_t), 44, output);

    uint16_t buffer;
    while(fread(&buffer, sizeof(uint16_t), 1, input)){
        buffer *= change;
        fwrite(&buffer, sizeof(uint16_t), 1, output);
    }

    fclose(input);
    fclose(output);

    return 0;
}