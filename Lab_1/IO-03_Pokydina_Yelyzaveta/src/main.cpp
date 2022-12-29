#include <stdio.h>
#include <stdlib.h>
#include "functions.h"

int main (int argc, char** argv){
  struct Wav file;
  uint16_t* data = NULL;
  readFile(&file, &data, "./Master Of Puppets.wav");
  changeVolume(&file, &data, 1.3f);
  createNewWav(&file, data, "./NewFile.wav");
  free(data);
}
