#include "WavManager.h"

int main()
{
    WavManager wavManager;

    wavManager.IncreaseVolume("../Master Of Puppets.wav", "OutFile_VolumeUp.wav");

    return 0;
}