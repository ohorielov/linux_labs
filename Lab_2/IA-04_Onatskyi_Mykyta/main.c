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

char *encode(char **code, FILE *inFilePtr, FILE *outFilePtr) {
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
  return resultBits;
}

void addBits(char **bits, char symbol) {
  char bitString[BITS_IN_BYTE + 1];
  bitString[BITS_IN_BYTE] = '\0';

  //symbol to binary ?itoa?
  for (int i = 0; i < BITS_IN_BYTE; ++i) {
    bitString[i] = '0' + (symbol >> (BITS_IN_BYTE - 1 - i) & 1);
  }

  char *buffer = (char *) malloc((strlen(*bits) + 1) * sizeof(char));
  strcpy(buffer, *bits);
  free(*bits);
  *bits = (char *) malloc((strlen(buffer) + BITS_IN_BYTE + 1) * sizeof(char));
  strcpy(*bits, buffer);
  strncat(*bits, bitString, BITS_IN_BYTE);

}

int codeIndex(char **code, char *buffer) {
  for (int i = 0; i < ASCII_COUNT; ++i) {
    if (code[i] != NULL && strcmp(code[i], buffer) == 0)
      return i;
  }
  return -1;
}

void decode(char **code, char *bits) {
  size_t len = strlen(bits);
  char *result = (char *) malloc(len * sizeof(char));
  char buffer[BITS_IN_BYTE * 4];
  size_t resultLen = 0;
  size_t bufferSize = 0;
  result[0] = '\0';
  buffer[0] = '\0';
  for (int i = 0; i < len; i++) {
    int index = codeIndex(code, buffer);
    if (index != -1) {
//      printf("index for string %s = %d\n",buffer, index);
      result[resultLen] = (char) index;
      result[++resultLen] = '\0';
      buffer[0] = '\0';
      bufferSize = 0;
      i--;
    } else {
      buffer[bufferSize] = bits[i];
      buffer[++bufferSize] = '\0';
    }
  }
  printf("%s\n", result);
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

  char *bits = encode(code, initFile, outputFile);
//  printf("bits: %s", bits);
  rewind(initFile);
  fclose(outputFile);

  outputFile = fopen("compressed_text.txt", "rb");

  decode(code, bits);

//  compare();

  fclose(initFile);
  fclose(outputFile);

  free(frequencies);
  free(arr);
  free(freq);

  return 0;
}
