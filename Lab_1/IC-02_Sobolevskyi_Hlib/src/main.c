#include "../include/wav.h"

int main()
{
    WAV* wav = load_wav("../Master Of Puppets.wav");
    
    float scale = 1;
    printf("Enter volume scale: ");
    scanf("%f", &scale);
    
    save_wav(wav, scale, "test.wav");
    return 0;
}