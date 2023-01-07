#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

#include "wav_header.h"

int16_t* read_wav(int file, struct wav_header* wav);
void write_data(int fd, struct wav_header* wav, int16_t* data);
void change_volume(struct wav_header* wav, int16_t* data, int volume);
int16_t calculate_scale(int volume_percentage, int16_t sample);
int16_t normalize(int16_t value);
