#include <iostream>
#include <string>
#include <cstdlib>
#include <cstdio>
#include <fstream>
#include "wav.h"


int main(int argc, char **argv) {
    if (argc != 3)
        std::cout << "Usage: ./Foo wav_filename new_filename" << std::endl;
    else {
        std::ifstream input_wav(argv[1], std::ios::binary);
        std::ofstream output_wav(argv[2], std::ios::binary);
        Wav wav_file = {};

        if(input_wav.is_open()) {
            if(output_wav.is_open()) {
                input_wav.read((char*)&wav_file.ChunkID, 4);
            input_wav.read((char*)&wav_file.ChunkSize, 4);
            input_wav.read((char*)&wav_file.Format, 4);
            input_wav.read((char*)&wav_file.Subchunk1ID, 4);
            input_wav.read((char*)&wav_file.Subchunk1Size, 4);
            input_wav.read((char*)&wav_file.AudioFormat, 2);
            input_wav.read((char*)&wav_file.NumChannels, 2);
            input_wav.read((char*)&wav_file.SampleRate, 4);
            input_wav.read((char*)&wav_file.ByteRate, 4);
            input_wav.read((char*)&wav_file.BlockAlign, 2);
            input_wav.read((char*)&wav_file.BitsPerSample, 2);
            input_wav.read((char*)&wav_file.Subchunk2ID, 4);
            input_wav.read((char*)&wav_file.Subchunk2Size, 4); 

            output_wav.write((char*) &wav_file.ChunkID, 4);
            output_wav.write((char*) &wav_file.ChunkSize, 4);
            output_wav.write((char*) &wav_file.Format, 4);
            output_wav.write((char*) &wav_file.Subchunk1ID, 4);
            output_wav.write((char*) &wav_file.Subchunk1Size, 4);
            output_wav.write((char*) &wav_file.AudioFormat, 2);
            output_wav.write((char*) &wav_file.NumChannels, 2);
            output_wav.write((char*) &wav_file.SampleRate, 4);
            output_wav.write((char*) &wav_file.ByteRate, 4);
            output_wav.write((char*) &wav_file.BlockAlign, 2);
            output_wav.write((char*) &wav_file.BitsPerSample, 2);
            output_wav.write((char*) &wav_file.Subchunk2ID, 4);
            output_wav.write((char*) &wav_file.Subchunk2Size, 4);

            BYTE data;
            while(input_wav) {
                input_wav.read((char*) &data, sizeof(BYTE));
                wav_file.Data = data / 2;
                output_wav.write((char*) &wav_file.Data, sizeof(BYTE));
            }
            
            input_wav.close();
            output_wav.close();
            }
            else {
                std::cout << "Opening file error!" << std::endl;
            }
        }
        else {
            std::cout << "Opening file error!" << std::endl;
        }
        
    }
    return 0;
}   