#include "header.h"

#define input_file "..//Master Of Puppets.wav"
#define output_file "edited.wav"
#define WAV_INFO(str, field) (printf("%s %u \n", (str), (wav_binary->_##field)))
#define WAV_INFO_CHAR(str, field) (printf("%s %.4s \n", (str), (wav_binary->_##field)))

int read_wav(wav *wav_binary){
    FILE *input_data=fopen(input_file,"rb");
    if (input_data == NULL){
        printf("Can't open");
        return 0;
    }
    fread(&wav_binary->_chunkID, 4, 1, input_data);
    fread(&wav_binary->_ChunkSize, 4, 1, input_data);
    fread(&wav_binary->_Format, 4, 1, input_data);
    fread(&wav_binary->_Subchunk1ID, 4, 1, input_data);
    fread(&wav_binary->_Subchunk1Size, 4, 1, input_data);
    fread(&wav_binary->_AudioFormat, 2, 1, input_data);
    fread(&wav_binary->_NumChannels, 2, 1, input_data);
    fread(&wav_binary->_SampleRate, 4, 1, input_data);
    fread(&wav_binary->_ByteRate, 4, 1, input_data);
    fread(&wav_binary->_ByteAlign, 2, 1, input_data);
    fread(&wav_binary->_BitsPerSample, 2, 1, input_data);
    fread(&wav_binary->_Subchunk2ID, 4, 1, input_data);
    fread(&wav_binary->_Subchunk2Size, 4, 1, input_data);
    wav_binary->_Data = (uint16_t*)malloc(wav_binary->_Subchunk2Size);
    fread(wav_binary->_Data, wav_binary->_Subchunk2Size, 1, input_data);
    fclose(input_data);

    
}

int out_wav(wav *wav_binary){
    FILE *out_data=fopen(output_file,"wb");
    
    if (out_data == NULL){
         printf("Can't create");
        return 0;
    }
    int chunk_i =wav_binary->_Subchunk2Size / sizeof(uint16_t);
    double volume_up= pow(10,0.3);  //m=10^(n/10), n-db 
    fwrite(&wav_binary->_chunkID, 4, 1, out_data);
    fwrite(&wav_binary->_ChunkSize, 4, 1, out_data);
    fwrite(&wav_binary->_Format, 4, 1, out_data);
    fwrite(&wav_binary->_Subchunk1ID, 4, 1, out_data);
    fwrite(&wav_binary->_Subchunk1Size, 4, 1, out_data);
    fwrite(&wav_binary->_AudioFormat, 2, 1, out_data);
    fwrite(&wav_binary->_NumChannels, 2, 1, out_data);
    fwrite(&wav_binary->_SampleRate, 4, 1, out_data);
    fwrite(&wav_binary->_ByteRate, 4, 1, out_data);
    fwrite(&wav_binary->_ByteAlign, 2, 1, out_data);
    fwrite(&wav_binary->_BitsPerSample, 2, 1, out_data);
    fwrite(&wav_binary->_Subchunk2ID, 4, 1, out_data);
    fwrite(&wav_binary->_Subchunk2Size, 4, 1, out_data);
    for (uint32_t i = 0; i<chunk_i;i++){
        uint16_t chunk= wav_binary->_Data[i];
        chunk*= volume_up;
        wav_binary->_Data[i]=chunk;
    }
    fwrite(wav_binary->_Data, wav_binary->_Subchunk2Size, 1, out_data);
    fclose(out_data);
}
void print_header(wav *wav_binary){
    WAV_INFO_CHAR("ChunkID:", chunkID);
    WAV_INFO("ChunkSize", ChunkSize);
    WAV_INFO_CHAR("Format:", Format);
    WAV_INFO_CHAR("Subchunk1ID:", Subchunk1ID);
    WAV_INFO("Subchunk1Size", Subchunk1Size);
    WAV_INFO("AudioFormat", AudioFormat);
    WAV_INFO("NumChannels", NumChannels);
    WAV_INFO("SampleRate", SampleRate);
    WAV_INFO("ByteRate", ByteRate);
    WAV_INFO("ByteAlign", ByteAlign);
    WAV_INFO("BitsPerSample", BitsPerSample);
    WAV_INFO_CHAR("Subchunk2ID:", Subchunk2ID);
    WAV_INFO("Subchunk2Size", Subchunk2Size);

}