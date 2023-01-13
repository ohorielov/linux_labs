#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "huffman.c"

#define ASCII_COUNT 256
#define BITS_IN_BYTE 8

int *getFrequencies(FILE *filePtr) {

  int *frequencies = (int *) calloc(ASCII_COUNT, sizeof(int));
  char symbol;

  while ((symbol = fgetc(filePtr)) != EOF)
    frequencies[(int) symbol]++;

  return frequencies;
}

// https://www.programmingsimplified.com/c/source-code/c-program-bubble-sort
void bubble_sort(char *arr[], int *freq[], int size) {
  int i, j;
  int temp1;
  char temp2;

  for (i = 0; i < size - 1; i++) {
    for (j = 0; j < size - i - 1; j++) {
      if ((*freq)[j] > (*freq)[j + 1]) {
        temp1 = (*freq)[j];
        (*freq)[j] = (*freq)[j + 1];
        (*freq)[j + 1] = temp1;
        temp2 = (*arr)[j];
        (*arr)[j] = (*arr)[j + 1];
        (*arr)[j + 1] = temp2;
      }
    }
  }
}

void encode(char **code, FILE *inFilePtr, FILE *outFilePtr) {
  char symbol;
  char *resultBits = (char *) malloc(0);


  rewind(inFilePtr);

  while ((symbol = fgetc(inFilePtr)) != EOF) {
    char *buffer = (char *) malloc((strlen(resultBits) + 1) * sizeof(char));
    strcpy(buffer, resultBits);
    free(resultBits);
    resultBits = (char *) malloc((strlen(buffer) + strlen(code[symbol]) + 1) * sizeof(char));
    strcpy(resultBits, buffer);
    strncat(resultBits, code[symbol], strlen(code[symbol]));
  }
  int i;
  for (i = 0; i <= strlen(resultBits) - BITS_IN_BYTE; i += BITS_IN_BYTE) {
    char buffer[BITS_IN_BYTE + 1];
    buffer[BITS_IN_BYTE] = '\0';
    for (int j = i, k = 0; j < i + BITS_IN_BYTE; j++, k++)
      buffer[k] = resultBits[j];
    printf("%s\n", buffer);
    char byte = strtol(buffer, 0, 2);
    fputc(byte, outFilePtr);
  }
  if (i < strlen(resultBits)) {
    char buffer[BITS_IN_BYTE + 1] = "00000000";
    for (int j = 0; i < strlen(resultBits); i++, j++) {
      buffer[j] = resultBits[i];
    }
    char byte = strtol(buffer, 0, 2);
    fputc(byte, outFilePtr);
  }
}

int main(void) {

  FILE *initFile = fopen("non_compressed_text.txt", "r");
  FILE *outputFile = fopen("compressed_text.txt", "w");
  int *frequencies = getFrequencies(initFile);

  char *arr = malloc(ASCII_COUNT * sizeof(char));
  int *freq = malloc(ASCII_COUNT * sizeof(int));
  int size = 0;

  for (int i = 0; i < ASCII_COUNT; i++) {
    if (frequencies[i] != 0) {
      arr[size] = (char) i;
      freq[size] = frequencies[i];
      size++;
    }
  }

  bubble_sort((char **) &arr, (int **) &freq, size);

  char **code = HuffmanCodes(arr, freq, size);

  encode(code, initFile, outputFile);

  free(frequencies);
  free(arr);
  free(freq);

  return 0;
}
