#include "wav_header.h"

#define in_file "..//Master Of Puppets.wav"
#define res_file "MoF(edited).wav"
#define db 3

int wav_reader(struct wav *song){
FILE *input = fopen(in_file, "rb");
if(input == NULL){
printf("No file found!");
return 0;
}

fread(&song->chunkID, 4, 1, input);
fread(&song->ChunkSize, 4, 1, input);
fread(&song->Format, 4, 1, input);
fread(&song->Subchunk1ID, 4, 1, input);
fread(&song->Subchunk1Size, 4, 1, input);
fread(&song->AudioFormat, 2, 1, input);
fread(&song->NumChannels, 2, 1, input);
fread(&song->SampleRate, 4, 1, input);
fread(&song->ByteRate, 4, 1, input);
fread(&song->ByteAlign, 2, 1, input);
fread(&song->BitsPerSample, 2, 1, input);
fread(&song->Subchunk2ID, 4, 1, input);
fread(&song->Subchunk2Size, 4, 1, input);

song-> Data = (uint16_t*)malloc(song->Subchunk2Size);
fread(song->Data, song->Subchunk2Size, 1, input);
fclose(input);
}

int wav_output(struct wav *song){
FILE *out_data=fopen(res_file, "wb");

if (out_data == NULL){
printf("FILE WASN`T CREATED");
return 0;
}
int chunk_i = song->Subchunk2Size / sizeof(uint16_t);
double volume_inc = pow(10, 0.3);
fwrite(&song -> chunkID, 4, 1, out_data);
fwrite(&song -> ChunkSize, 4, 1, out_data);
fwrite(&song -> Format, 4, 1, out_data);
fwrite(&song -> Subchunk1ID, 4, 1, out_data);
fwrite(&song -> Subchunk1Size, 4, 1, out_data);
fwrite(&song -> AudioFormat, 2, 1, out_data);
fwrite(&song -> NumChannels, 2, 1, out_data);
fwrite(&song -> SampleRate, 4, 1, out_data);
fwrite(&song -> ByteRate, 4, 1, out_data);
fwrite(&song -> ByteAlign, 2, 1, out_data);
fwrite(&song -> BitsPerSample, 2, 1, out_data);
fwrite(&song -> Subchunk2ID, 4, 1, out_data);
fwrite(&song -> Subchunk2Size, 4, 1, out_data);

for (uint32_t i=0; i<chunk_i; i++){
uint16_t chunk = song->Data[i];
chunk*=volume_inc;
song->Data[i]=chunk;
}

fwrite(song->Data, song->Subchunk2Size, 1, out_data);
fclose(out_data);
}
