#include "WavChanger.h"
#define input "Master Of Puppets.wav"
#define output "Master Of Puppets (Changed).wav"
#define VOLUME 0.5

int main() 
{
    struct WavHeader wav_header = {};
    //Open the .wav file 
    FILE *file_input = fopen(input, "rb");
    //Read the .wav file
    WavRead(file_input, &wav_header);
    //Print information about the audio file
    WavPrint(&wav_header);
    //Change audio volume
    VolumeChange(&wav_header, VOLUME);
    //Open the file for the record 
    FILE* file_output = fopen(output, "wb");
    //Write the file
    WavWrite(file_output, &wav_header);
    return 0;
}
