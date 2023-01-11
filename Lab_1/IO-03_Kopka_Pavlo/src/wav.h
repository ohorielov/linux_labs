#include <iostream>

#ifndef LINUX_LABS_WAV_H
#define LINUX_LABS_WAV_H

#endif //LINUX_LABS_WAV_H

#define RIFF_SIZE 12
#define FORMAT_CHUNK_SIZE 24
#define DATA_CHUNK_SIZE 8

#define WAV_METADATA_SIZE (RIFF_SIZE + FORMAT_CHUNK_SIZE + DATA_CHUNK_SIZE)


struct wav_riff {
    uint32_t chunk_id;
    uint32_t chunk_size;
    uint32_t format;
};

struct wav_format {
    uint32_t subchunk_id;
    uint32_t subchunk_size;
    uint16_t audio_format;
    uint16_t num_of_channels;
    uint32_t sample_rate;
    uint32_t byte_rate;
    uint16_t block_align;
    uint16_t bits_per_sample;
};

struct wav_data {
    uint32_t subchunk_id;
    uint32_t subchunk_size;
    uint8_t *data;
};

struct wav {
    wav_riff riff;
    wav_format format;
    wav_data data;
};

wav *read_wav(char *filename) {
    wav *_wav = (wav *) malloc(sizeof(wav));

    FILE *fd = fopen(filename, "r");

    if (fd == NULL) {
        std::cout << "Cant open input file" << std::endl;
        exit(-1);
    }

    fseek(fd, 0L, SEEK_END);
    uint64_t fsize = ftell(fd);
    rewind(fd);

    _wav->data.data = (uint8_t *) malloc(fsize);

    fread((uint8_t *) &_wav->riff, 1, RIFF_SIZE, fd);
    fread((uint8_t *) &_wav->format, 1, FORMAT_CHUNK_SIZE, fd);
    fread((uint8_t *) &_wav->data, 1, DATA_CHUNK_SIZE, fd);
    fread((uint8_t *) _wav->data.data, 1, fsize - WAV_METADATA_SIZE, fd);
    fclose(fd);

    return _wav;
}

void multiply_wav_db(wav *file, float value) {
    int data_size = file->data.subchunk_size;
    int chunk_size = file->format.bits_per_sample / 8;

    for (int i = 0; i < data_size; i += chunk_size) {
        int16_t *chunk = ((int16_t *) (file->data.data + i));
        *chunk *= value;
    }
}

void save_wav(wav *file, char *filename) {
    FILE *fd = fopen(filename, "w");

    if (fd == NULL) {
        std::cout << "Cant open output file" << std::endl;
        exit(-1);
    }

    fwrite((uint8_t *) &file->riff, RIFF_SIZE, 1, fd);
    fwrite((uint8_t *) &file->format, FORMAT_CHUNK_SIZE, 1, fd);
    fwrite((uint8_t *) &file->data, DATA_CHUNK_SIZE, 1, fd);

    fwrite((uint8_t *) file->data.data, file->data.subchunk_size, 1, fd);

    fclose(fd);
}