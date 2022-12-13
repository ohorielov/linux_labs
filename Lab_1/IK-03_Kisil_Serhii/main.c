#include "changerwav.h"
#define input "Master Of Puppets.wav"
#define output "Master Of Puppets (New).wav"
#define volume 0.5

int main() 
{
    struct WavHeader wav_header = {};
    //Open the .wav file 
    FILE *file_input = fopen(input, "rb");
    //Read the .wav file
    read(file_input, &wav_header);
    //Print information about the audio file
    print(&wav_header);
    //Change audio volume
    volumechange(&wav_header, volume);
    //Open the file for the record 
    FILE* file_output = fopen(output, "wb");
    //Write the file
    write(file_output, &wav_header);
    return 0;
}