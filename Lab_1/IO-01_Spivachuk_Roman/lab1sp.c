#include "lab1sp.h"


int main(int argc, char **argv) {
    if (argc != 4) {
        printf("Wrong parameter count. Usage: ./%s File_from_read File_to_write Multiply_value\n", *argv);
        exit(1);
    }

    FILE *fp, *new_fp;
    fp = fopen(*(argv + 1), "r");
    new_fp = fopen(*(argv + 2), "w");
    float change_value = atof(*(argv + 3));

    if (!fp) {
        fprintf(stderr, "%s file can't be opened\n", *(argv + 1));
        exit(1);
    }

    if (!new_fp) {
        fprintf(stderr, "%s file can't be opened\n", *(argv + 2));
        exit(1);
    }

    union header_data *file_header = (union header_data *) malloc(HEADER_SIZE);

    for (int i = 0; i < HEADER_SIZE && (file_header->data[i] = getc(fp)) != EOF; i++);

    printf("ChunkID: %.4s\n", file_header->header.id_descr.chunk_id_s);
    printf("Chunk size: %u\n", file_header->header.chunk_size);
    printf("Format: %.4s\n", file_header->header.format_descr.format_s);

    printf("Subchunk 1 ID: %s\n", file_header->header.subchunk1_descr.subchunk1_id_s);
    printf("Subchunk 1 size: %u\n", file_header->header.subchunk1_size);
    printf("Audio format: %u\n", file_header->header.audio_format_descr.audio_format);
    printf("Number of channels: %us\n", file_header->header.num_channels);
    printf("Sample rate: %u\n", file_header->header.sample_rate);
    printf("Byte rate: %u\n", file_header->header.byte_rate);
    printf("Block align: %us\n", file_header->header.block_align);
    printf("Bits per sample: %us\n", file_header->header.bits_per_sample);

    printf("Subchunk 2 ID: %.4s\n", file_header->header.subchunk2_descr.subchunk2_id_s);
    printf("Subchunk 2 size: %u\n", file_header->header.subchunk2_size);

    printf("\nChanging volume of wav file\n");



    // writing header of read file to the new file

    for (int i = 0; i < HEADER_SIZE; i++) {
        putc( file_header->data[i], new_fp);
    }

    // writing edited data to the new file
    uint16_t buffer;
    while (fread(&buffer, 2, 1, fp)) {
        buffer = buffer * (float)change_value;
        fwrite(&buffer, 2, 1, new_fp);
    }

    fclose(fp);
    fclose(new_fp);
    exit(0);
}
