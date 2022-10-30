#include "wavProcessor.h"

int main(int args, char* argv[])
{
    Wav *wav = read_wav("Master Of Puppets.wav");
    make_wav_volume_down (wav, 2);
    print_wav_header(wav);
    
    printf("Written bytes count: %d", write_wav(wav, "Master Of Puppets volume down.wav"));

    free(wav->Data.AudioData);
    free(wav);
    return 0;
}   
