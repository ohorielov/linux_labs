struct WAV_HEADER {
char riff[4];
int riff_size;
char wave[4];
char fmt[4];
int fmt_size;
short audio_format;
short nun_channels;
int sample_rate;
int byte_rate;
short block_align;
short bits_per_sample;
char data[4]
int data_size;
};

int read_wav_file(const char *filename, struct WAV_HEADER *header, short **audio_data);
void decrease_volume(short *audio_data, int data_size, float factor);
int write_wav_file(const char *filename, struct WAV_HEADER header, short *audio_data, int data_size);
