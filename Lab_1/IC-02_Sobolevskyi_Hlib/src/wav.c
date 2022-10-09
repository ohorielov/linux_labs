#include "../include/wav.h"

WAV* load_wav(const char* filename)
{
    WAV* wav = (WAV*)malloc(sizeof(WAV));
    
    FILE* file = fopen(filename, "rb");
    if (!file)
    {
        puts("Could not open file");
        puts(filename);
        exit(EXIT_FAILURE);
    }

    fseek(file, 0L, SEEK_END);
    uint64_t file_size = ftell(file);
    rewind(file);
    
    wav->data_subchunk.data = (uint8_t*)malloc(file_size);

    printf("%llu\n", fread((uint8_t*)&wav->riff, 1, RIFF_SIZE, file));
    printf("%llu\n", fread((uint8_t*)&wav->fmt_subchunk, 1, FMT_CHANK_SIZE, file));
    printf("%llu\n", fread((uint8_t*)&wav->data_subchunk, 1, DATA_CHANK_SIZE, file));
    printf("%llu\n", fread(wav->data_subchunk.data, 1, file_size - WAV_METADATA_SIZE, file));
    
    fclose(file);
    printf("filesize: %llu\n", file_size);
    printf("===riff===\n");
    printf("id: %u\n", wav->riff.id);
    printf("size: %u\n", wav->riff.chuck_size);
    printf("format: %c%c%c%c\n",
        ((char*)(&wav->riff.format))[0],
        ((char*)(&wav->riff.format))[1],
        ((char*)(&wav->riff.format))[2],
        ((char*)(&wav->riff.format))[3]);

    printf("\n===format chunk===\n");
    printf("id: %u\n", wav->fmt_subchunk.id);
    printf("size: %u\n", wav->fmt_subchunk.size);
    printf("audio_format: %hu\n", wav->fmt_subchunk.format);
    printf("num_channels: %hu\n", wav->fmt_subchunk.num_channels);
    printf("sample_rate: %u\n", wav->fmt_subchunk.sample_rate);
    printf("byte_rate: %u\n", wav->fmt_subchunk.byte_rate);
    printf("block_align: %hu\n", wav->fmt_subchunk.block_align);
    printf("bits_per_sample: %hu\n", wav->fmt_subchunk.bits_per_sample);
    
    printf("\n===data chunk===\n");
    printf("id: %u\n", wav->data_subchunk.id);
    printf("size: %u\n", wav->data_subchunk.size);
    printf("cant print actual data\n");
    return wav;
}

void update_wav(WAV* wav)
{
    // for (int i = 0; i < sizeof(wav->data_subchunk.data) / sizeof(uint8_t); i++)
    // {
    //     wav->data_subchunk.data[i] *= 1.1;
    // }
}

void save_wav(WAV* wav, const char* filename)
{
    FILE* file = fopen(filename, "w");
    if (!file)
    {
        puts("Could not open file");
        puts(filename);
        exit(EXIT_FAILURE);
    }

    fwrite((uint8_t*)&wav->riff, 1, RIFF_SIZE, file);
    fwrite((uint8_t*)&wav->fmt_subchunk, 1, FMT_CHANK_SIZE, file);
    fwrite((uint8_t*)&wav->data_subchunk, 1, DATA_CHANK_SIZE, file);
    fwrite(wav->data_subchunk.data, 1, wav->data_subchunk.size, file);

    fclose(file);
}