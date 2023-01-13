#include <stdio.h>
#include <stdlib.h>

char* inFileName = "./Master Of Puppets.wav";
char* outFileName = "./Output.wav";
double scale = 1.4f;

struct WAVFile {
//The "RIFF" chunk descriptor
  long int ChunkID;
  long int ChunkSize;
  long int Format;

//The fmt sub-chunk
  long int Subchunk1ID;
  long int Subchunk1Size;
  short int AudioFormat;
  short int NumChannels;
  long int SampleRate;
  long int ByteRate;
  short int BlockAlign;
  short int BitsPerSample;

//The data sub-chunk
  long int Subchunk2ID;
  unsigned long int Subchunk2Size;
};

void readFile(struct WAVFile * header, short int** data) {
  FILE* inFile = fopen(inFileName, "rb");
  if (inFile == NULL) {
    printf("No '%s' in the folder", inFileName);
    exit(-1);
  }

  fread(header, sizeof(struct WAVFile), 1, inFile);
  *data = malloc(header->Subchunk2Size);
  fread(*data, header->Subchunk2Size, 1, inFile);
  fclose(inFile);
}

void amplify(struct WAVFile * header, short int** data) {
  unsigned long int samplesCount = header->Subchunk2Size / sizeof(short int);
  for(int i = 0; i < samplesCount; i++) {
    (*data)[i] = (short int)((*data)[i] * scale);
  }
}

void createNewFile(struct WAVFile * header, short int* data) {
  FILE* newWAV = fopen(outFileName, "wb");
  if (newWAV == NULL){
    free(data);
    printf("Can't create %s file", outFileName);
    exit(-1);
  }
  fwrite(header, sizeof(struct WAVFile), 1, newWAV);
  fwrite(data, header->Subchunk2Size, 1, newWAV);
  fclose(newWAV);
}

int main (int argc, char** argv) {
  struct WAVFile header;
  short int* data = NULL;

  readFile(&header, &data);
  amplify(&header, &data);
  createNewFile(&header, data);
  free(data);
}
