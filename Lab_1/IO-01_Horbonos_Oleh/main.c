#include <stdio.h>
#include <stdlib.h>

#include "wav_header.h"
#include "wav_processor.h"

int main(int argc, char** argv)
{
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
