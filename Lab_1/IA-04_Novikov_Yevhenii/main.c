#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <printf.h>
#include <errno.h>
#include <stdlib.h>

#ifndef BUF_SIZE
#define BUF_SIZE (1024)
#endif


struct wav_header {
    char chunk_id[4];
    u_int32_t chunk_size;
    char format[4];

    char subchunk1_id[4];
    u_int32_t subchunk1_size;
    u_int16_t audio_format;
    u_int16_t num_channels;
    u_int32_t sample_rate;
    u_int32_t byte_rate;
    u_int16_t block_align;
    u_int16_t bits_per_sample;

    char subchunk2_id[4];
    u_int32_t subchunk2_size;
    char *data;
};

void print_header(struct wav_header header);

int main() {
    char buf[BUF_SIZE];
    int fd;
    ssize_t numRead;

    fd = open("Master Of Puppets.wav", O_RDWR);
    if (errno != 0) {
        printf("open file err: %d\n", errno);
        return errno;
    }

    struct wav_header header;

    read(fd, &header.chunk_id, sizeof header.chunk_id);
    read(fd, &header.chunk_size, 4);
    read(fd, &header.format, 4);

    read(fd, &header.subchunk1_id, 4);
    read(fd, &header.subchunk1_size, 4);
    read(fd, &header.audio_format, 2);
    read(fd, &header.num_channels, 2);
    read(fd, &header.sample_rate, 4);
    read(fd, &header.byte_rate, 4);
    read(fd, &header.block_align, 2);
    read(fd, &header.bits_per_sample, 2);

    read(fd, &header.subchunk2_id, 4);
    read(fd, &header.subchunk2_size, 4);


    ssize_t data_size = header.subchunk2_size - 8;
    header.data = (char *) malloc(data_size);
    read(fd, header.data, data_size);

    print_header(header);

    printf("data: %s\n", header.data);
}

void print_header(struct wav_header header){
    printf("chunk_id: %.*s\n", 4, header.chunk_id);
    printf("chunk_size: %u\n", header.chunk_size);
    printf("format: %.*s\n", 4, header.format);

    printf("subchunk1_id: %.*s\n", 4, header.subchunk1_id);
    printf("subchunk1_size: %u\n", header.subchunk1_size);
    printf("audio_format: %hu\n", header.audio_format);
    printf("num_channels: %hu\n", header.num_channels);
    printf("sample_rate: %u\n", header.sample_rate);
    printf("byte_rate: %u\n", header.byte_rate);
    printf("block_align: %hu\n", header.block_align);
    printf("bits_per_sample: %hu\n", header.bits_per_sample);
    printf("subchunk2_id: %.*s\n", 4, header.subchunk2_id);
    printf("subchunk2_size: %u\n", header.subchunk2_size);
}