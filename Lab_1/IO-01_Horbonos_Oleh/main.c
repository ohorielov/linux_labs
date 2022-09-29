#include <stdio.h>
#include <stdlib.h>

#include "wav_header.h"
#include "wav_processor.h"

int main(int argc, char** argv)
{
    // wav_header wav;
    // int fd_wav = open(argv[1], O_RDONLY);
    // int ret = read(fd_wav, &wav, sizeof(wav_header));
    // //printf("%d %d\n", wav.fmt.blockAlign,  wav.fmt.bitsPerSample);
    // int16_t* data = malloc(wav.data.dataSize);
    // ret = read(fd_wav, data, wav.data.dataSize);
    // int volume = 300;
    // for(int i = 0; i < wav.data.dataSize / (wav.fmt.blockAlign / wav.fmt.numChanels); ++i)
    // {
    //     int16_t samp = data[i];
    //     if(volume > 100)
    //         samp += (int16_t) (data[i] * (volume - 100) / 100);
    //     else
    //         samp -= (int16_t) (data[i] * (100 - volume) / 100);
    //     data[i] = samp;
    // }
    // int fd_out = open("result.wav", O_WRONLY | O_CREAT);
    // write(fd_out, &wav, sizeof(wav_header));
    // write(fd_out, data, wav.data.dataSize);
    // close(fd_wav);
    // close(fd_out);
    // free(data);

    if(argc != 4 )
    {
        printf("Usage: ./wav_processor <in file> <volume> <out file>\n");
        return 1;
    }

    wav_header wav;
    
    int16_t* data = read_wav(argv[1], &wav);
    if(data == NULL)
    {
        return 1;
    }
    
    process_data(&wav, data, atoi(argv[2]));

    int ret = write_data(argv[3], &wav, data);
    free(data);
    if(ret == ERROR)
    {
        return 1;
    }

    return 0;
}