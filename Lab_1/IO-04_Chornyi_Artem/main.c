#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>

struct header_struct //Structure for storing header data
{
    char chunk_id[4];
    uint32_t chunk_size;
    char format[4];
    char subchunk1_id[4];
    uint32_t subchunk1_size;
    uint16_t audio_format;
    uint16_t num_channels;
    uint32_t sample_rate;
    uint32_t byte_rate;
    uint16_t block_align;
    uint16_t bits_per_sample;
    char subchunk2_id[4];
    uint32_t subchunk2_size;
};

struct file_struct 
{
    uint16_t *data;
    struct header_struct header;
};

struct file_struct audio_file;

void read(char* input_file_name)
{
    FILE* input_file_pointer;

    input_file_pointer = fopen(input_file_name, "r");

    if (!input_file_pointer)
    {
        fprintf(stderr, "%s file is not open\n", input_file_name);
        return NULL;
    }

    //The "Riff" chunk descriptor
    fread(&audio_file.header.chunk_id, 4, 1, input_file_pointer);
    fread(&audio_file.header.chunk_size, 4, 1, input_file_pointer);
    fread(&audio_file.header.format, 4, 1, input_file_pointer);

    //The "fmt" sub-chunk
    fread(&audio_file.header.subchunk1_id, 4, 1, input_file_pointer);
    fread(&audio_file.header.subchunk1_size, 4, 1, input_file_pointer);
    fread(&audio_file.header.audio_format, 2, 1, input_file_pointer);
    fread(&audio_file.header.num_channels, 2, 1, input_file_pointer);
    fread(&audio_file.header.sample_rate, 4, 1, input_file_pointer);
    fread(&audio_file.header.byte_rate, 4, 1, input_file_pointer);
    fread(&audio_file.header.block_align, 2, 1, input_file_pointer);
    fread(&audio_file.header.bits_per_sample, 2, 1, input_file_pointer);

    //The "data" sub-chunk
    fread(&audio_file.header.subchunk2_id, 4, 1, input_file_pointer);
    fread(&audio_file.header.subchunk2_size, 4, 1, input_file_pointer);

    //Read the raw data inside the "data" sub-chunk
    audio_file.data = (uint16_t*) malloc((audio_file.header.subchunk2_size));

    for (int i = 0; i < audio_file.header.subchunk2_size / (audio_file.header.bits_per_sample / 8); i++)
    {
        fread(&audio_file.data[i], audio_file.header.bits_per_sample / 8, 1, input_file_pointer);
    }

    //Closing file read stream
    fclose(input_file_pointer);
}

int write(char* output_file_name, float volume_diff_value)
{
    FILE* output_file_pointer;

    output_file_pointer = fopen(output_file_name, "w");

    if (!output_file_pointer) //If the file cannot be opened, the programme is terminated because it cannot continue
    {
        fprintf(stderr, "%s file cannot be opened\n", output_file_name);
        return NULL;
    }

    //Writing the header of the output audio file
    //The "Riff" chunk descriptor
    fwrite(&audio_file.header.chunk_id, 4, 1, output_file_pointer);
    fwrite(&audio_file.header.chunk_size, 4, 1, output_file_pointer);
    fwrite(&audio_file.header.format, 4, 1, output_file_pointer);

    //The "fmt" sub-chunk
    fwrite(&audio_file.header.subchunk1_id, 4, 1, output_file_pointer);
    fwrite(&audio_file.header.subchunk1_size, 4, 1, output_file_pointer);
    fwrite(&audio_file.header.audio_format, 2, 1, output_file_pointer);
    fwrite(&audio_file.header.num_channels, 2, 1, output_file_pointer);
    fwrite(&audio_file.header.sample_rate, 4, 1, output_file_pointer);
    fwrite(&audio_file.header.byte_rate, 4, 1, output_file_pointer);
    fwrite(&audio_file.header.block_align, 2, 1, output_file_pointer);
    fwrite(&audio_file.header.bits_per_sample, 2, 1, output_file_pointer);

    //The "data" sub-chunk
    fwrite(&audio_file.header.subchunk2_id, 4, 1, output_file_pointer);
    fwrite(&audio_file.header.subchunk2_size, 4, 1, output_file_pointer);

    // Writing edited raw data
    uint16_t volume_data;

    for (int i = 0; i < audio_file.header.subchunk2_size / (audio_file.header.bits_per_sample / 8); i++)
    {
        volume_data = (audio_file.data[i]);
        volume_data = volume_data * pow(10, 0.01 * (float)volume_diff_value);

        fwrite(&volume_data, audio_file.header.bits_per_sample / 8, 1, output_file_pointer);
    }

    //Closing file write stream
    fclose(output_file_pointer);

    return 1;
}

int main(int argc, char** argv) 
{
    if (argc != 4) //The function takes n+1 parameters in the following order: incoming file, outgoing file, volume difference in dB
    {
        printf("Incorrect number of parameters\n", *argv);  //If the number of parameters does not match, the programme cannot continue
        return 0;
    }

    read(argv[1]); //The first parameter should always be the incoming file

    float volume_diff_value_value = atof(argv[3]); //The third parameter should always be the volume difference in dB
    
    if (write(argv[2], volume_diff_value_value) == NULL) //The second parameter should always be the output file
    {
        printf("Write error\n");  //If the number of parameters does not match, the programme cannot continue
        return 0;
    }
    
    return 0;
}
