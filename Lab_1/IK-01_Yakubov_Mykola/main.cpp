#include <iostream>
#include <cstdlib>
#include <string>
#include <fstream>
#include <cstdint>
#include <cstring>
#include <cmath>
#include <unistd.h>

typedef struct  WavHeader
{
    uint32_t         ChunkID;        
    uint32_t        ChunkSize;      
    uint32_t         Format;        
    uint32_t         Subchunk1ID;        
    uint32_t        Subchunk1Size;  
    uint16_t        AudioFormat;    
    uint16_t        NumOfChan;      
    uint32_t        SamplesPerSec;  
    uint32_t        bytesPerSec;    
    uint16_t        blockAlign;    
    uint16_t        bitsPerSample;  
    uint32_t         Subchunk2ID;
    uint32_t        Subchunk2Size; 
} wav_hdr;

int16_t* readFileData (FILE* wavFile, wav_hdr WavHeader, uint64_t numOfSamples) {
    int16_t* wavData = new int16_t[numOfSamples];
    std::cout << numOfSamples << "\n";
    fread(wavData, WavHeader.bitsPerSample/8, numOfSamples, wavFile);
    return wavData;
}

void writeHeader (FILE* wavFile, wav_hdr WavHeader) {
    fwrite(&WavHeader, sizeof(wav_hdr), 1, wavFile);
}

void writeFileData (FILE* wavFile, int16_t* fileData, wav_hdr WavHeader, uint64_t numOfSamples) {
    int i = 0;
    fwrite(fileData, WavHeader.bitsPerSample/8, numOfSamples, wavFile);
}

void changeVolume(int16_t* fileData, wav_hdr WavHeader, double k, uint64_t numOfSamples){
    int i = 0;
    while(i<numOfSamples){
        fileData[i] = (int16_t)(fileData[i]*k);
        i++;
    }
}

int main(){
    wav_hdr WavHeader;
    FILE *wavFile;
    FILE *newFile;
    const char *NEW_FILE_NAME = "./new file.wav";
    int headerSize = sizeof(WavHeader);
    const char* filePath = "./Master_Of_Puppets.wav";
    
    wavFile = fopen(filePath, "rb");
    if(wavFile == NULL){
        std::cout << "Can't open wav file!";
    }
    fread(&WavHeader,headerSize, 1, wavFile);
    int16_t *fileData;
    uint64_t numOfSamples = WavHeader.ChunkSize/(WavHeader.bitsPerSample/8);
    fileData = readFileData(wavFile, WavHeader, numOfSamples);
    changeVolume(fileData, WavHeader, 2, numOfSamples);
    fclose(wavFile);
    newFile = fopen(NEW_FILE_NAME, "wb");
    writeHeader(newFile, WavHeader);
    writeFileData(newFile, fileData, WavHeader, numOfSamples);
    return 0;
}