#include "../include/wav.h"

int main()
{
    WAV* wav = load_wav("../CantinaBand3.wav");
    save_wav(wav, "test.wav");
    return 0;
}