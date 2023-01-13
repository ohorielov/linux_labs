#include "WAVHandler.h"

int main()
{
    WAV* wav = loadWAVFile("../Master Of Puppets.wav");
    handleWAV(wav, "volumeLowered.wav");
    releaseMemory(wav);
    return 0;
}