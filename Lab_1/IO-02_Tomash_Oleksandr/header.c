#include "header.h"

#define input_file "..//Master Of Puppets.wav"
#define output_file "edited.wav"
#define db 3

int read_wav(struct wav *puppets){
    FILE *input_data=fopen(input_file,"rb");
    if (input_data == NULL){
        printf("Can't open");
        return 0;
    }
    fread(&puppets->chunkID, 4, 1, input_data);
    fread(&puppets->ChunkSize, 4, 1, input_data);
    fread(&puppets->Format, 4, 1, input_data);
    fread(&puppets->Subchunk1ID, 4, 1, input_data);
    fread(&puppets->Subchunk1Size, 4, 1, input_data);
    fread(&puppets->AudioFormat, 2, 1, input_data);
    fread(&puppets->NumChannels, 2, 1, input_data);
    fread(&puppets->SampleRate, 4, 1, input_data);
    fread(&puppets->ByteRate, 4, 1, input_data);
    fread(&puppets->ByteAlign, 2, 1, input_data);
    fread(&puppets->BitsPerSample, 2, 1, input_data);
    fread(&puppets->Subchunk2ID, 4, 1, input_data);
    fread(&puppets->Subchunk2Size, 4, 1, input_data);
    puppets->Data = (uint16_t*)malloc(puppets->Subchunk2Size);
    fread(puppets->Data, puppets->Subchunk2Size, 1, input_data);
    fclose(input_data);

    // printf("ChunkID: %c%c%c%c\n",
    //     ((char*)(&puppets->chunkID))[0],
    //     ((char*)(&puppets->chunkID))[1],
    //     ((char*)(&puppets->chunkID))[2],
    //     ((char*)(&puppets->chunkID))[3]);
    // printf("ChunkSize: %u\n", puppets->ChunkSize);
    // printf("Format: %c%c%c%c\n",
    //     ((char*)(&puppets->Format))[0],
    //     ((char*)(&puppets->Format))[1],
    //     ((char*)(&puppets->Format))[2],
    //     ((char*)(&puppets->Format))[3]);
    // printf("Subchunk1ID: %c%c%c\n",
    //     ((char*)(&puppets->Subchunk1ID))[0],
    //     ((char*)(&puppets->Subchunk1ID))[1],
    //     ((char*)(&puppets->Subchunk1ID))[2]);
    // printf("Subchunk1Size: %u\n", puppets->Subchunk1Size);
    // printf("AudioFormat: %u\n", puppets->AudioFormat);
    // printf("NumChannels: %u\n", puppets->NumChannels);
    // printf("SampleRate: %u\n", puppets->SampleRate);
    // printf("ByteRate: %u\n", puppets->ByteRate);
    // printf("ByteAlign: %u\n", puppets->ByteAlign);
    // printf("BitsPerSample: %u\n", puppets->BitsPerSample);
    // printf("Subchunk2ID: %c%c%c%c\n",
    //     ((char*)(&puppets->Subchunk2ID))[0],
    //     ((char*)(&puppets->Subchunk2ID))[1],
    //     ((char*)(&puppets->Subchunk2ID))[2],
    //     ((char*)(&puppets->Subchunk2ID))[3]);
    // printf("Subchunk2Size: %u\n", puppets->Subchunk2Size);
    
}

int out_wav(struct wav *puppets){
    FILE *out_data=fopen(output_file,"wb");
    
    if (out_data == NULL){
         printf("Can't create");
        return 0;
    }
    int chunk_i =puppets->Subchunk2Size / sizeof(uint16_t);
    double volume_up= pow(10,0.3);  //m=10^(n/10), n-db 
    fwrite(&puppets->chunkID, 4, 1, out_data);
    fwrite(&puppets->ChunkSize, 4, 1, out_data);
    fwrite(&puppets->Format, 4, 1, out_data);
    fwrite(&puppets->Subchunk1ID, 4, 1, out_data);
    fwrite(&puppets->Subchunk1Size, 4, 1, out_data);
    fwrite(&puppets->AudioFormat, 2, 1, out_data);
    fwrite(&puppets->NumChannels, 2, 1, out_data);
    fwrite(&puppets->SampleRate, 4, 1, out_data);
    fwrite(&puppets->ByteRate, 4, 1, out_data);
    fwrite(&puppets->ByteAlign, 2, 1, out_data);
    fwrite(&puppets->BitsPerSample, 2, 1, out_data);
    fwrite(&puppets->Subchunk2ID, 4, 1, out_data);
    fwrite(&puppets->Subchunk2Size, 4, 1, out_data);
    for (uint32_t i = 0; i<chunk_i;i++){
        uint16_t chunk= puppets->Data[i];
        chunk*= volume_up;
        puppets->Data[i]=chunk;
    }
    fwrite(puppets->Data, puppets->Subchunk2Size, 1, out_data);
    fclose(out_data);
}