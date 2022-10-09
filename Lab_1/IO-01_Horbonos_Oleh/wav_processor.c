#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <err.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <unistd.h>

#include "wav_processor.h"

int16_t* read_wav(const char* file, wav_header* wav)
{
    int fd = open(file, O_RDONLY);
    if(fd < 0)
    {
        printf("Error while opening file for reading.\n");
        close(fd);
        return NULL;
    }

    int ret = read(fd, wav, sizeof(wav_header));
    if(ret < sizeof(wav_header))
    {
        printf("Error while reading wav header.\n");
        close(fd);
        return NULL;
    }

    int16_t* data = malloc(wav->data.dataSize);
    if(data == NULL)
    {
        printf("Error while reading wav header.\n");
        close(fd);
        return NULL;
    }

    ret = read(fd, data, wav->data.dataSize);
    if(ret < wav->data.dataSize)
    {
        printf("Error while reading wav header.\n");
        free(data);
        close(fd);
        return NULL;
    }

    close(fd);
    return data;
}

void process_data(wav_header* wav, int16_t* data, int volume)
{
    for(int i = 0; i < wav->data.dataSize / (wav->fmt.blockAlign / wav->fmt.numChanels); ++i)
    {
        int16_t samp = data[i];
        if(volume > 100)
            samp += (int16_t) (data[i] * (volume - 100) / 100);
        else
            samp -= (int16_t) (data[i] * (100 - volume) / 100);
        data[i] = samp;
    }
}

int write_data(const char* file, wav_header* wav, int16_t* data)
{
    int fd = open(file, O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IROTH);
    if(fd < 0)
    {
        printf("Error while opening file for writing.\n");
        close(fd);
        return ERROR;
    }

    int ret = write(fd, wav, sizeof(wav_header));
    if(ret < sizeof(wav_header))
    {
        printf("Error while writing wav header.\n");
        close(fd);
        return ERROR;
    }

    ret = write(fd, data, wav->data.dataSize);
    if(ret < wav->data.dataSize)
    {
        printf("Error while writing wav header.\n");
        close(fd);
        return ERROR;
    }

    close(fd);
    return SUCCESS;
}