#include "wav_reader.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

// WAV header chunks sizes
#define WAV_HEADER_SIZE 44

int wav_load(wav_t *wav, const char *filename) {
    if (wav == NULL) {
        return -1;
    }

    // Open file
    int fd = open(filename, O_RDONLY);
    if (fd == -1) {
        fprintf(stderr, "Failed to open file \"%s\"\n", filename);
        return -1;
    }

    // Get file size
    wav->file_size = lseek(fd, 0, SEEK_END);
    lseek(fd, 0, SEEK_SET);

    // Read meta data
    read(fd, wav, WAV_HEADER_SIZE);

    if (wav->fmt.bit_depth == 32 && wav->fmt.audio_format == 3) {
        wav->sample_format = SF_FLOAT32;
    } else if (wav->fmt.bit_depth == 16 && wav->fmt.audio_format == 1) {
        wav->sample_format = SF_INT16;
    } else {
        wav->sample_format = SF_FLOAT32;
        fprintf(stderr, "WAV fail has %d bits per sample, it's not supported!\n", wav->fmt.bit_depth);
    }

    // Read WAV data
    wav->data.data = malloc(wav->file_size - WAV_HEADER_SIZE);
    read(fd, wav->data.data, wav->file_size - WAV_HEADER_SIZE);

    close(fd);
    return 1;
}

int wav_change_volume(wav_t *wav, float factor) {
    if (wav == NULL) {
        return -1;
    }

    int size = (wav->file_size - WAV_HEADER_SIZE) / wav->sample_format;
    for (int i = 0; i < size; i++) {
        switch (wav->sample_format) {
            case SF_INT16: {
                int16_t *data = (int16_t *)wav->data.data;
                double scaled_value = floor(data[i] * factor) + 0.5;

                // Clamp new value
                if (scaled_value >= INT16_MAX) {
                    data[i] = INT16_MAX;
                } else if (scaled_value <= INT16_MIN) {
                    data[i] = INT16_MIN;
                } else {
                    data[i] = (int16_t)scaled_value;
                }

                break;
            }
            case SF_FLOAT32: {
                ((float *)wav->data.data)[i] = floor(((float *)wav->data.data)[i] * factor) + 0.5;
                break;
            }
        }
    }

    return 1;
}

int wav_save(wav_t* wav, const char *filename) {
    if (wav == NULL) {
        return -1;
    }

    int fd = creat(filename, S_IRUSR | S_IWUSR);
    if (fd == -1) {
        fprintf(stderr, "Failed to create file \"%s\"\n", filename);
        return -1;
    }

    write(fd, wav, WAV_HEADER_SIZE);
    write(fd, wav->data.data, wav->file_size - WAV_HEADER_SIZE);

    close(fd);
    return 1;
}

void wav_clear(wav_t* wav) {
    free(wav->data.data);
}
