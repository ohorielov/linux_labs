#include <stdio.h>
#include <stdlib.h>
#include "wav_volume_changer.h"


int16_t* read_wav(int fd, struct wav_header* wav) {
    read(fd, wav, sizeof(struct wav_header));
    int16_t* data = malloc(wav->data.sample_data_length);
    read(fd, data, wav->data.sample_data_length);
    close(fd);
    return data;
}


void change_volume(struct wav_header* wav, int16_t* sample_data, int volume_percentage)
{
    for(int i = 0; i < wav->data.sample_data_length / (wav->fmt.block_align / wav->fmt.channels); i++)
    {
        int16_t changed = calculate_scale(volume_percentage, sample_data[i]);
        sample_data[i] = normalize(changed);
    }
}


int16_t calculate_scale(int volume_percentage, int16_t sample) {
    if(volume_percentage > 100) {
        return sample + ((int16_t)(sample*(volume_percentage-100)/100));
    }
    else {
        return sample - ((int16_t)(sample*(100-volume_percentage)/100));
    }
}


int16_t normalize(int16_t value) {
    if (value > INT16_MAX) return INT16_MAX;
    if (value < INT16_MIN) return INT16_MIN;
    return value;
}


void write_data(int fd, struct wav_header* wav, int16_t* data) {
    int ret = write(fd, wav, sizeof(struct wav_header));
    ret = write(fd, data, wav->data.sample_data_length);
    close(fd);
}
