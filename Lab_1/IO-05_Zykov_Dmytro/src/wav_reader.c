#include "wav_reader.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

// WAV header chunks sizes
#define RIFF_SIZE       12
#define FMT_SIZE        24
#define DATA_SIZE       8
#define METADATA_SIZE   (RIFF_SIZE + FMT_SIZE + DATA_SIZE)

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
    read(fd, wav, METADATA_SIZE);

    // Read WAV data
    wav->data.data = (int16_t *)malloc(wav->file_size - METADATA_SIZE);
    read(fd, wav->data.data, wav->file_size - METADATA_SIZE);

    close(fd);
    return 1;
}

int wav_change_volume(wav_t *wav, float factor) {
    if (wav == NULL) {
        return -1;
    }

    int size = (wav->file_size - METADATA_SIZE) / sizeof(int16_t);
    for (int i = 0; i < size; i++) {
        double scaled_value = floor((wav->data.data[i] * factor) + 0.5);

        // Clamp new value
        if (scaled_value >= INT16_MAX) {
            wav->data.data[i] = INT16_MAX;
        } else if (scaled_value <= INT16_MIN) {
            wav->data.data[i] = INT16_MIN;
        } else {
            wav->data.data[i] = (int16_t)scaled_value;
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

    write(fd, wav, METADATA_SIZE);
    write(fd, wav->data.data, wav->file_size - METADATA_SIZE);

    close(fd);
    return 1;
}

void wav_clear(wav_t* wav) {
    free(wav->data.data);
}
