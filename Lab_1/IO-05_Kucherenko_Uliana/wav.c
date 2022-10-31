#include "wav.h"

#include <stdio.h>
#include <stdlib.h>

// Linux API
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>

#define WAV_HEADER_SIZE 44

Wav *WavOpen(const char *path) {
    Wav *wav = (Wav *)malloc(sizeof(Wav));
    if (!wav) {
        return NULL;
    }

    int file = open(path, O_RDONLY);
    if (file == -1) {
        printf("%s", "Can't open file!\n");
        return NULL;
    }

    uint64_t size = lseek(file, 0, SEEK_END) - WAV_HEADER_SIZE;
    lseek(file, 0, SEEK_SET);

    read(file, wav, WAV_HEADER_SIZE);

    wav->_Data = (int16_t *)malloc(size);
    if (!wav->_Data) {
        return NULL;
    }

    read(file, wav->_Data, size);

    close(file);

    return wav;
}

void WavWrite(Wav *wav, const char *path) {
    if (!wav)
        return;
   
    int file = creat(path, S_IRUSR | S_IWUSR);
    if (file == -1) {
        printf("%s", "Can't create file!\n");
        return;
    }

    write(file, wav, WAV_HEADER_SIZE);
    write(file, wav->_Data, wav->_Subchunk2Size);

    close(file);
}

void WavSetVolume(Wav *wav, float volume) {
    if (!wav)
        return;

    uint64_t size = wav->_Subchunk2Size / sizeof(int16_t);
    for (int i = 0; i < size; ++i) {
        wav->_Data[i] *= volume;
    }
}

void WavFree(Wav *wav) {
    if (!wav)
        return;

    free(wav->_Data);
    free(wav);
}
