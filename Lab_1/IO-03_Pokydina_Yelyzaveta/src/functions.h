#include <stdio.h>
#include <stdlib.h>

struct Wav {
  uint32_t ChunkID;
  uint32_t ChunkSize;
  uint32_t Format;
  uint32_t Subchunk1ID;
  uint32_t Subchunk1Size;
  uint16_t AudioFormat;
  uint16_t NumChannels;
  uint32_t SampleRate;
  uint32_t ByteRate;
  uint16_t BlockAlign;
  uint16_t BitsPerSample;
  uint32_t Subchunk2ID;
  uint32_t Subchunk2Size;
};

void readFile(struct Wav * file, uint16_t** data, char* wavFile){
  FILE* fileToRead = fopen(wavFile, "rb");

  if (fileToRead == NULL){
    printf("File does not exist.");
    exit(-1);
  }

  fread(file, sizeof(struct Wav), 1, fileToRead);
  *data = malloc(file->Subchunk2Size);
  fread(*data, file->Subchunk2Size, 1, fileToRead);
  fclose(fileToRead);
}

void changeVolume(struct Wav * file, uint16_t** data, double value){
  uint32_t samplesCount = file->Subchunk2Size / sizeof(uint16_t);

  for(int i = 0; i < samplesCount; i++){
    (*data)[i] = (uint16_t)((*data)[i] * value);
  }
}

void createNewWav(struct Wav * file, uint16_t* data, char* newWavFile){
  FILE* newWav = fopen(newWavFile, "wb");

  fwrite(file, sizeof(struct Wav), 1, newWav);
  fwrite(data, file->Subchunk2Size, 1, newWav);
  fclose(newWav);
}
