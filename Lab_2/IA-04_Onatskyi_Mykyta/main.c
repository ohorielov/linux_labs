#include <stdlib.h>
#include <stdio.h>
#include "huffman.c"

#define ASCII_COUNT 256
int * getFrequencies(FILE * filePtr) {

  int * frequencies = (int *) calloc(ASCII_COUNT, sizeof(int));
  char symbol;

  while ((symbol = fgetc(filePtr)) != EOF)
    frequencies[(int) symbol]++;

  return frequencies;
}

// https://www.programmingsimplified.com/c/source-code/c-program-bubble-sort
void bubble_sort(char *arr[], int *freq[], int size)
{
  int i, j;
  int temp1;
  char temp2;

  for (i = 0 ; i < size - 1; i++) {
    for (j = 0 ; j < size - i - 1; j++) {
      if ((*freq)[j] > (*freq)[j+1]) {
        temp1 = (*freq)[j];
        (*freq)[j] = (*freq)[j+1];
        (*freq)[j+1] = temp1;
        temp2 = (*arr)[j];
        (*arr)[j] = (*arr)[j+1];
        (*arr)[j+1] = temp2;
      }
    }
  }
}

int main(void) {

  FILE *initFile = fopen("non_compressed_text.txt", "r");
  int *frequencies = getFrequencies(initFile);

  char *arr = malloc(ASCII_COUNT * sizeof (char));
  int *freq = malloc(ASCII_COUNT * sizeof (int));
  int size = 0;

  for (int i = 0; i < ASCII_COUNT; i++){
    if (frequencies[i] != 0){
      arr[size] = (char) i;
      freq[size] = frequencies[i];
      size++;
    }
  }

  bubble_sort((char **) &arr, (int **) &freq, size);

  for (int i = 0; i < size; i++) {
//    printf("Arr[]: '%c' Freq[] %d\n", arr[i], freq[i]);
//    printf("%d\n", frequencies[i]);
  }

  HuffmanCodes(arr, freq, size);

//  Encode()

  free(frequencies);
  free(arr);
  free(freq);

  return 0;
}
