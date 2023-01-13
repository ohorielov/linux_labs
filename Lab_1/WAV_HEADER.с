#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "WAV_HEADER.h"


int read_wav_file (const char *filename, struct WAV_HEADER *header, short **audio_data)
  //Open the input file in binary mode
  FILE *input_file = fopen(filename, "rb");
  //CHeck if file was opened successfully
  if (!input_file) {
  printf( "Error opening input file: %s\n", filename);
  return 1;
  }
  
  //Read the header infromation from the file
  fread( header, sizeof (struct WAV_HEADER), 1, input_file);
  
  //Check if the file is .wav valid file
  if (memcmp( header->riff, "RIFF", 4) || memcmp( header->>wave, "WAVE", 4) ||
  memcmp(header->fmt, "fmt", 4) || memcmp( header->>data, "data", 4) {
  fclose(input_file);
  return 1;
  }
  
  int data_size = header->data_size;
  //Allocate memory for the audio data
  *audio_data = (short *)malloc(data_size);
  //REad the audio data from file
  fread(*audio_data, 1, data_size, input_file);
  fclose(input_file);
  return 0;
}


void decrease_volume(short *audio_data, int data_size, float factor) {
   if (factor < 0) factor = 0;
   if (factor > 1) factor = 1;
   //Multiply each sample by the factor to decrease volume
   for (int 1 = 0; 1 < data_size / sizeof(short); i++) {
       audio_data[i] = audio_data[i] * factor;
   )
   
int write_wav_file(const char *filename, struct WAV_HEADER header, short *audio_data, int data_size) {
   //OPen file in binary mode
   FILE *output_file = fopen(filename, "wb");
   //Check if file was opened successfully
   if (!output_file) {
       printf("Error opening output file: %s\n", filename);
       return 1;
   }
   header.data_size = data_size;
   
   // Update the RIFF size field in the header
   header.riff_size = data_size + sizeof(struct WAV_HEADER) - 8;
   //Write the header to the output file
   
   fwrite(&header, sizeof(struct WAV_HEADER), 1, output_file);
   //WRITE the audio data data to the output file
   fwrite(audio_data, 1, data_size, output_file);
   fclose(output_file);
   
   return 0;
}



  
