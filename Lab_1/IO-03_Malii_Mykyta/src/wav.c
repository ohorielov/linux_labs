#include "wav.h"

#ifndef LAB_1_WAVE_H
#define LAB_1_WAVE_H

#endif
#define FOUR_BYTES 4
#define TWO_BYTES 2
#define VOLUME_CHANGE_VALUE 3
#define WAV_FILE_HEADER_SIZE 44



WAV_HEADER* openFile(char* filename) {

    WAV_HEADER* header = (WAV_HEADER*)malloc(sizeof(WAV_HEADER));

    FILE* file = fopen(filename, "rb");
    if(file == NULL){
        printf("File not found");
        exit(1);
    }

    // RIFF
    fread((&header->id), 1, FOUR_BYTES, file);
    fread((&header->size), 1, FOUR_BYTES, file);
    fread((&header->format), 1, FOUR_BYTES, file);

    //The fmt sub-chunk
    fread((&header->subchunk1Id), 1, FOUR_BYTES, file);
    fread((&header->subchunk1Size), 1, FOUR_BYTES, file);
    fread((&header->audioFormat), 1, TWO_BYTES, file);
    fread((&header->numChannels), 1, TWO_BYTES, file);
    fread((&header->sampleRate), 1, FOUR_BYTES, file);
    fread((&header->byteRate), 1, FOUR_BYTES, file);
    fread((&header->blockAlign), 1, TWO_BYTES, file);
    fread((&header->bitsPerSample), 1, TWO_BYTES, file);

    //The data sub-chunk
    fread((&header->subchunk2Id), 1, FOUR_BYTES, file);
    fread((&header->subchunk2Size), 1, FOUR_BYTES, file);

    header->wavData = (uint8_t*)malloc(header->subchunk2Size);
    fread(header->wavData, header->subchunk2Size, 1, file);


    fclose(file);

    printf("\nThe RIFF chunk descriptor\n");

    printf("Id: %c%c%c%c \n%u\n",
           ((char*)(&header->id))[0],
           ((char*)(&header->id))[1],
           ((char*)(&header->id))[2],
           ((char*)(&header->id))[3],
           header-> id);

    printf("Size: %u, Kb: %u\n", header->size, header->size/1024);


    printf("Format: %c%c%c%c \n%u \n",
           ((char*)(&header->format))[0],
           ((char*)(&header->format))[1],
           ((char*)(&header->format))[2],
           ((char*)(&header->format))[3],
           header->format);

    printf("\nThe fmt sub-chunk\n");

    printf("Subchunk id: %c%c%c%c \n%u\n",

           ((char*)(&header->subchunk1Id))[0],
           ((char*)(&header->subchunk1Id))[1],
           ((char*)(&header->subchunk1Id))[2],
           ((char*)(&header->subchunk1Id))[3],
           header->subchunk1Id);

    printf("Subchunk size: %u\n", header->subchunk1Size);

    char format_name[10] = "";

    if (header->audioFormat == 1)
        strcpy(format_name,"PCM");
    else if (header->audioFormat == 6)
        strcpy(format_name, "A-law");
    else if (header->audioFormat == 7)
        strcpy(format_name, "Mu-law");

    printf("Audio format: %s \n%u \n",
           format_name,
           header->audioFormat);

    printf("Number of channels: %u \n", header->numChannels);

    printf("Sample Rate: %u \n", header->sampleRate);

    printf("Byte Rate: %u Bit Rate: %u\n", header->byteRate, header->byteRate*8);

    printf("Block Alignment: %u \n", header->blockAlign);

    printf("Bits per sample: %u \n", header->bitsPerSample);

    printf("\nThe data sub-chunk\n");

    printf("Data marker: %c%c%c%c \n%u\n",
           ((char*)(&header->subchunk2Id))[0],
           ((char*)(&header->subchunk2Id))[1],
           ((char*)(&header->subchunk2Id))[2],
           ((char*)(&header->subchunk2Id))[3],
           header->subchunk2Id);

    printf("Size of data chunk: %u \n", header->subchunk2Size);

    printf("Size of each sample: %u \n", (header->numChannels * header->bitsPerSample) / 8);

    return header;
}


void changeVolume(WAV_HEADER* header, bool riseUp){

    for (uint32_t i = 0; i < header->subchunk2Size; i++){
        if(riseUp) {
            header->wavData[i] = (int8_t)(header->wavData[i] * VOLUME_CHANGE_VALUE);
        }
        else{
            header->wavData[i] = (int8_t)(header->wavData[i] / VOLUME_CHANGE_VALUE);
        }
    }
}

void saveInNewFile(WAV_HEADER* header, char *filename){
    FILE *file = fopen(filename, "wb");

    fwrite(header, WAV_FILE_HEADER_SIZE, 1, file);
    fwrite(header->wavData, header->subchunk2Size, 1, file);

    fclose(file);
}
