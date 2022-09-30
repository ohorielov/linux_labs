#include "wav_reader.h"

#include <stdio.h>
#include <stdlib.h>
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
    wav->data.data = (uint8_t *)malloc(wav->file_size - METADATA_SIZE);
    read(fd, wav->data.data, wav->file_size - METADATA_SIZE);

    close(fd);
    return 1;
}
