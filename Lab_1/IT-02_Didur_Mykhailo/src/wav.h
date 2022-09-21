#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

#define RIFF_SIZE 12
#define FMT_CHNK_SIZE 24

// that is without actual data
#define DATA_CHNK_SIZE 8

#define WAV_METADATA_SIZE (RIFF_SIZE + FMT_CHNK_SIZE + DATA_CHNK_SIZE)

char wav_format_str[4] = {'W', 'A', 'V', 'E'};
uint32_t wav_format = *(uint32_t*)(wav_format_str);

struct riff // 12 bytes
{
    uint32_t id;
    uint32_t size;
    uint32_t format;
};

struct fmt_chunk // 24
{
    uint32_t id;
    uint32_t size;
    uint16_t audio_format;
    uint16_t num_channels;
    uint32_t sample_rate;
    uint32_t byte_rate;
    uint16_t block_align;
    uint16_t bits_per_sample;
};

struct data_chunk // 8 + ptr
{
    uint32_t id;
    uint32_t size;
    uint8_t *data;
};

struct wav
{
    riff _riff;
    fmt_chunk _fmt;
    data_chunk _data;
};

void reverse(uint8_t* data, size_t length) {
    for(size_t i = 0; i < length / 2; i++) {
        uint8_t temp = data[i];
        data[i] = data[length - i];
        data[length - i] = temp;
    }
}

void to_little_end_all(wav* _wav) {
//    reverse((uint8_t*)&_wav->_riff.id, 4);
//    reverse((uint8_t*)&_wav->_fmt.id, 4);
//    reverse((uint8_t*)&_wav->_data.id, 4);
}

wav* load_wav(char* filename) {
    wav* _wav = (wav*)malloc(sizeof(wav));

    // load from file
    FILE* fd = fopen(filename, "r");
    if(fd == NULL) {
        puts("Cant open file");
        exit(-1);
    }

    fseek(fd , 0L , SEEK_END);
    uint64_t fsize = ftell(fd);
    rewind(fd);

    _wav->_data.data = (uint8_t*)malloc(fsize);

    fread((uint8_t*)&_wav->_riff, 1, RIFF_SIZE, fd); // riff
    fread((uint8_t*)&_wav->_fmt, 1, FMT_CHNK_SIZE, fd); // fmt chunk
    fread((uint8_t*)&_wav->_data, 1, DATA_CHNK_SIZE, fd); // data chunk metadata
    fread((uint8_t*)_wav->_data.data, 1, fsize - WAV_METADATA_SIZE, fd); // actual data

    fclose(fd);

    to_little_end_all(_wav);

    return _wav;
}

void free_wav(wav* _wav) {
    free(_wav->_data.data);
    free(_wav);
}

void wav_dump(wav* _wav) {
    printf("===riff===\n");
    printf("id: %c%c%c%c\n",
        ((char*)(&_wav->_riff.id))[0],
        ((char*)(&_wav->_riff.id))[1],
        ((char*)(&_wav->_riff.id))[2],
        ((char*)(&_wav->_riff.id))[3]);

    printf("size: %u\n", _wav->_riff.size);
    printf("format: %c%c%c%c\n",
        ((char*)(&_wav->_riff.format))[0],
        ((char*)(&_wav->_riff.format))[1],
        ((char*)(&_wav->_riff.format))[2],
        ((char*)(&_wav->_riff.format))[3]);

    printf("\n===format chunk===\n");
    printf("id: %c%c%c%c\n",
        ((char*)(&_wav->_fmt.id))[0],
        ((char*)(&_wav->_fmt.id))[1],
        ((char*)(&_wav->_fmt.id))[2],
        ((char*)(&_wav->_fmt.id))[3]);
        
    printf("size: %u\n", _wav->_fmt.size);
    printf("audio_format: %hu\n", _wav->_fmt.audio_format);
    printf("num_channels: %hu\n", _wav->_fmt.num_channels);
    printf("sample_rate: %u\n", _wav->_fmt.sample_rate);
    printf("byte_rate: %u\n", _wav->_fmt.byte_rate);
    printf("block_align: %hu\n", _wav->_fmt.block_align);
    printf("bits_per_sample: %hu\n", _wav->_fmt.bits_per_sample);
    
    printf("\n===data chunk===\n");
    printf("id: %c%c%c%c\n",
        ((char*)(&_wav->_data.id))[0],
        ((char*)(&_wav->_data.id))[1],
        ((char*)(&_wav->_data.id))[2],
        ((char*)(&_wav->_data.id))[3]);

    printf("size: %u\n", _wav->_data.size);
    printf("cant print actual data\n");
}
