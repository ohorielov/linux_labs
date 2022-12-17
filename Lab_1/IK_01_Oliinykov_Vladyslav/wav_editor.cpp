#include <iostream>
#include <cstdio>
#include <fstream>
#include <cstring>

using namespace std;

struct WAV_Struct{
    char                 ChunkID[4];
    unsigned int         ChunkSize;
    char                 Format[4];
    char                 Subchunk1ID[4];
    unsigned int         Subchunk1Size;
    void*                Subchunk1data;
    unsigned short       AudioFormat;
    unsigned short       NumChannels;
    unsigned int         SampleRate;
    unsigned int         ByteRate;
    unsigned short       BlockAlign;
    unsigned short       BitsPerSample;
    char                 Subchunk2ID[4];
    unsigned int         Subchunk2Size;
    void*                Subchunk2data;
};

void DisplayWAVInfo(WAV_Struct wav_struct)
{
    cout << "--------------------------------------" << endl;
    printf("WAV File Header read:\n");
    printf("File Type: %c%c%c%c\n", wav_struct.ChunkID[0], wav_struct.ChunkID[1],
                                    wav_struct.ChunkID[2], wav_struct.ChunkID[3]);
    printf("File Size: %d\n", wav_struct.ChunkSize);
    printf("WAV Marker: %c%c%c%c\n", wav_struct.Format[0], wav_struct.Format[1],
                                     wav_struct.Format[2], wav_struct.Format[3]);
    printf("Format Name: %c%c%c%c\n", wav_struct.Subchunk1ID[0], wav_struct.Subchunk1ID[1],
                                      wav_struct.Subchunk1ID[2], wav_struct.Subchunk1ID[3]);
    printf("Format Length: %d\n", wav_struct.Subchunk1Size );
    printf("Format Type: %hd\n", wav_struct.AudioFormat);
    printf("Number of Channels: %hd\n", wav_struct.NumChannels);
    printf("Sample Rate: %d\n", wav_struct.SampleRate);
    printf("Sample Rate * Bits/Sample * Channels / 8: %d\n", wav_struct.ByteRate);
    printf("Bits per Sample * Channels / 8.1: %hd\n", wav_struct.BlockAlign);
    printf("Bits per Sample: %hd\n", wav_struct.BitsPerSample);
    printf("Bytes per Sample: %hd\n", wav_struct.BitsPerSample>>3);
    cout << "--------------------------------------" << endl;
    printf("Data section ID: %c%c%c%c\n", wav_struct.Subchunk2ID[0], wav_struct.Subchunk2ID[1],
                                          wav_struct.Subchunk2ID[2], wav_struct.Subchunk2ID[3]);
    printf("Data section size in bits: %d\n", wav_struct.Subchunk2Size);
    cout << "--------------------------------------" << endl;
}

WAV_Struct UpdateFile(WAV_Struct wav_struct, float modifier)
{
    void *sample = malloc(wav_struct.BitsPerSample>>3); // Allocate memory before copying to it

    for(unsigned long int i = 0; i <= wav_struct.Subchunk2Size; i+=wav_struct.BitsPerSample>>3)
    {
        memcpy(sample, wav_struct.Subchunk2data + i, wav_struct.BitsPerSample>>3);

        try
        {
            *(short *)sample *= modifier;
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }
        
        memcpy(wav_struct.Subchunk2data + i, sample, wav_struct.BitsPerSample>>3);
    }


    return wav_struct;
}

WAV_Struct HandleAction(WAV_Struct wav_struct)
{
    int action = -1;
    #define ActionIncrease 1
    #define ActionDecrease 2

    cout << "Select action:" << endl
         << "1. Increase volume" << endl
         << "2. Decrease volume" << endl
         << "Your choice: ";
    
    
    cin >> action;
    while(action != 1 && action != 2)
    {
        cout << "Wrong action." << endl << "Your choice: ";
        cin.clear();
        cin.ignore(10000, '\n');
        cin >> action;
    }

    float modifier;

    switch(action)
    {
        case ActionIncrease:
            modifier = 1.5;
            wav_struct = UpdateFile(wav_struct, modifier);
            break;
        case ActionDecrease:
            modifier = 0.5;
            wav_struct = UpdateFile(wav_struct, modifier);
            break;
        default:
            cout << "Unknown action." << endl;
            break;
    }

    return wav_struct;
}

void WriteNewFile(WAV_Struct wav_struct)
{
    string filename;
    
    cout << "Enter file name: ";
    getline(cin, filename);
    
    if(!filename.length())
        getline(cin, filename);
    
    cout << "Got filename: " << filename << endl;
    
    FILE* new_file = fopen(filename.c_str(), "wb");

    //Writing header
    fwrite(&wav_struct.ChunkSize, sizeof(wav_struct.ChunkSize), 1, new_file);
    fwrite(wav_struct.Format, sizeof(wav_struct.Format), 1, new_file);

    //Writing chunk 1
    fwrite(wav_struct.Subchunk1ID, sizeof(wav_struct.Subchunk1ID), 1, new_file);
    fwrite(&wav_struct.Subchunk1Size, sizeof(wav_struct.Subchunk1Size), 1, new_file);
    fwrite(wav_struct.Subchunk1data, wav_struct.Subchunk1Size, 1, new_file);

    //Writing chunk 2
    fwrite(wav_struct.Subchunk2ID, sizeof(wav_struct.Subchunk2ID), 1, new_file);
    fwrite(&wav_struct.Subchunk2Size, sizeof(wav_struct.Subchunk2Size), 1, new_file);
    fwrite(wav_struct.Subchunk2data, wav_struct.Subchunk2Size, 1, new_file);

    fclose(new_file);

    cout << "File written." << endl;
}


int read_wav(string filename)
{
    FILE* wav_file = fopen(filename.c_str(), "rb+");
    WAV_Struct wav_struct;

    if(!wav_file)
    {
        cout << "File failed to open." << endl;
        return 1;
    }

    // Reading header
    fread(wav_struct.ChunkID, sizeof(wav_struct.ChunkID), 1, wav_file);
    if(wav_struct.ChunkID[0] != 'R' ||
       wav_struct.ChunkID[1] != 'I' ||
       wav_struct.ChunkID[2] != 'F' ||
       wav_struct.ChunkID[3] != 'F')
    {
        cout << "WAV file header mismatch." << endl;
        return 2;
    }

    //Reading file size and format
    fread(&wav_struct.ChunkSize, sizeof(wav_struct.ChunkSize), 1, wav_file);
    fread(wav_struct.Format, sizeof(wav_struct.Format), 1, wav_file);

    //Reading chunk 1
    fread(wav_struct.Subchunk1ID, sizeof(wav_struct.Subchunk1ID), 1, wav_file);
    fread(&wav_struct.Subchunk1Size, sizeof(wav_struct.Subchunk1Size), 1, wav_file);
    wav_struct.Subchunk1data = malloc(wav_struct.Subchunk1Size);
    fread(wav_struct.Subchunk1data, wav_struct.Subchunk1Size, 1, wav_file);

    //Decode main information of chunk 1
    //Offsets
    #define AudioFormatOffset    0
    #define NumChannelsOffset    sizeof(wav_struct.AudioFormat)
    #define SampleRateOffset     NumChannelsOffset + sizeof(wav_struct.NumChannels)
    #define ByteRateOffset       SampleRateOffset + sizeof(wav_struct.SampleRate)
    #define BlockAlignOffset     ByteRateOffset + sizeof(wav_struct.ByteRate)
    #define BitsPerSampleOffset  BlockAlignOffset + sizeof(wav_struct.BlockAlign)
    memcpy(&wav_struct.AudioFormat, wav_struct.Subchunk1data + AudioFormatOffset, sizeof(wav_struct.AudioFormat));
    memcpy(&wav_struct.NumChannels, wav_struct.Subchunk1data + NumChannelsOffset, sizeof(wav_struct.NumChannels));
    memcpy(&wav_struct.SampleRate, wav_struct.Subchunk1data + SampleRateOffset, sizeof(wav_struct.SampleRate));
    memcpy(&wav_struct.ByteRate, wav_struct.Subchunk1data + ByteRateOffset, sizeof(wav_struct.ByteRate));
    memcpy(&wav_struct.BlockAlign, wav_struct.Subchunk1data + BlockAlignOffset, sizeof(wav_struct.BlockAlign));
    memcpy(&wav_struct.BitsPerSample, wav_struct.Subchunk1data + BitsPerSampleOffset, sizeof(wav_struct.BitsPerSample));

    //Reading chunk 2
    fread(wav_struct.Subchunk2ID, sizeof(wav_struct.Subchunk2ID), 1, wav_file);
    fread(&wav_struct.Subchunk2Size, sizeof(wav_struct.Subchunk2Size), 1, wav_file);
    wav_struct.Subchunk2data = malloc(wav_struct.Subchunk2Size);
    fread(wav_struct.Subchunk2data, wav_struct.Subchunk2Size, 1, wav_file);

    DisplayWAVInfo(wav_struct);

    wav_struct = HandleAction(wav_struct);

    WriteNewFile(wav_struct);

    return 0;
}

int main()
{
    string filename;
    
    cout << "Enter file name: ";
    getline(cin, filename);
    
    if(!filename.length())
        getline(cin, filename);
    
    cout << "Got filename: " << filename << endl;
    
    return read_wav(filename);
    
}
