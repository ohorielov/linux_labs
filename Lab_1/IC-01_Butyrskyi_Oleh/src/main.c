#include "wav_volume_changer.h"

#define input_file "../Master Of Puppets.wav"
#define output_file "../Master Of Puppets 2.wav"
#define volume_percentage 10


int main() {
    struct wav_header wav;

    int fd = open(input_file, O_RDONLY);
    int16_t* sample_data = read_wav(fd, &wav);

    change_volume(&wav, sample_data, volume_percentage);

    fd = creat(output_file, S_IRUSR | S_IWUSR);
    write_data(fd, &wav, sample_data);

    free(sample_data);
    return 0;
}
