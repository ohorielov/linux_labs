#include "wavProcessor.h"
        
Wav* read_wav(string path) {
    uint32_t wavFile;
    if ((wavFile = open(path, O_RDONLY)) == -1) {
        printf("Such a path does not exist or the file format is not .wav\n");
        return NULL;
    }

    Wav *myWav = (Wav*) malloc(HEADER_SIZE + sizeof(soundByte*));
    read(wavFile, myWav, HEADER_SIZE);

    myWav->Data.AudioData = (soundByte*) malloc(sizeof(soundByte) * myWav->Data.Subchunk2Size);
    printf("Count of bytes: %d", read(wavFile, myWav->Data.AudioData, myWav->Data.Subchunk2Size));

    printf("Size of wav: %d", sizeof(Wav));
    close(wavFile);
    return myWav;
}

void make_wav_volume_down(Wav *wav, uint8_t scaleValue)
{
    if (wav == NULL) {
        printf("The wav is empty\n");
        return;
    }

    for (uint32_t i = 0; i < wav->Data.Subchunk2Size; ++i) {
        soundByte newSound = (soundByte) (wav->Data.AudioData[i] / scaleValue);

        if (newSound > SOUND_BYTE_MAX) newSound = SOUND_BYTE_MAX;
        if (newSound < SOUND_BYTE_MIN) newSound = SOUND_BYTE_MIN;
     
        wav->Data.AudioData[i] = newSound;
    }
}

uint32_t write_wav(Wav* wav, string path) {
    if (wav == NULL) {
        printf("The wav is empty\n");
        return 0;
    }
    
    uint32_t wavFile = open(path, O_WRONLY | O_CREAT);
    
    uint32_t writtenBytes = 0;
    writtenBytes += write(wavFile, wav, HEADER_SIZE);
    writtenBytes += write(wavFile, wav->Data.AudioData, wav->Data.Subchunk2Size);


    close(wavFile);
    return writtenBytes;
}

void print_wav_header(Wav *wav) {
    printf("ChunkID: %c%c%c%c\n", wav->Riff.ChunkID[0], wav->Riff.ChunkID[1], 
        wav->Riff.ChunkID[2], wav->Riff.ChunkID[3]);
    printf("ChunkSize: %d\n", wav->Riff.ChunkSize);
    printf("Format: %c%c%c%c\n", wav->Riff.Format[0], wav->Riff.Format[1],
        wav->Riff.Format[2], wav->Riff.Format[3]);
    
    printf("Subchunk2ID: %c%c%c%c\n", wav->Fmt.Subchunk1ID[0], wav->Fmt.Subchunk1ID[1], 
        wav->Fmt.Subchunk1ID[2], wav->Fmt.Subchunk1ID[3]);
    printf("Subchunk1Size: %d\n", wav->Fmt.Subchunk1Size);
    printf("AudioFormat: %d\n", wav->Fmt.AudioFormat);
    printf("SampleRate: %d\n", wav->Fmt.SampleRate);
    printf("ByteRate : %d\n", wav->Fmt.ByteRate);
    printf("BlockAlign: %d\n", wav->Fmt.BlockAlign);
    printf("BitsPerSample: %d\n", wav->Fmt.BitsPerSample);

    printf("Subchunk2ID: %c%c%c%c\n", wav->Data.Subchunk2ID[0], wav->Data.Subchunk2ID[1], 
        wav->Data.Subchunk2ID[2], wav->Data.Subchunk2ID[3]);
    printf("Subchunk2Size: %d\n", wav->Data.Subchunk2Size);
}
