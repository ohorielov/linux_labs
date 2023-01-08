#include <stdio.h>
#include <stdlib.h>
#include "wav.h"

int main(int argc, char** argv) {
  if (argc != 4) {
    printf("Usage: %s <input_file> <output_file> <factor>\n", argv[0]);
    return 1;
  }

  // Open the input file
  FILE* input_file = fopen(argv[1], "rb");
  if (!input_file) {
    printf("Error: Failed to open input file\n");
    return 1;
  }

  // Read the WAV header
  wav_header_t header;
  fread(&header, sizeof(header), 1, input_file);

  // Calculate the number of samples in the audio data
  int num_samples = header.subchunk2_size / (header.bits_per_sample / 8);

  // Allocate memory to hold the audio data
  int16_t* samples = malloc(num_samples * sizeof(int16_t));
  if (!samples) {
    printf("Error: Failed to allocate memory for audio data\n");
    return 1;
  }

  // Read the audio data from the file
  fread(samples, sizeof(int16_t), num_samples, input_file);
  fclose(input_file);

  // Scale the volume of the audio data
  float volume = atof(argv[3]);
  for (int i = 0; i < num_samples; i++) {
    samples[i] = (int16_t)(samples[i] * volume);
  }

  // Open the output file
  FILE* output_file = fopen(argv[2], "wb");
  if (!output_file) {
    printf("Error: Failed to open output file\n");
    return 1;
  }

  // Write the modified header and audio data to the output file
  fwrite(&header, sizeof(header), 1, output_file);
  fwrite(samples, sizeof(int16_t), num_samples, output_file);
  fclose(output_file);

  // Clean up
  free(samples);

  return 0;
}
