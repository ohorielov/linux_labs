
struct wav_riff {
  char chunk_id[4];
  union int_data chunk_size;
  char format [4];
};
struct wav_fmt {
  char subchunkl_id[4];
  union int_data subchunk1_size;
  union short_data audio_format;
  union short_data num_channels;
  union int_data sample_rate;
  union int_data byte_rate;
  union short_data block_align;
  union short_data bits_per_sample;
};
struct wav_data {
  char subchunk2_id[4];
  union int_data subchunk2_size;
  union short_data *data;
};
union wav{
    byte data[HEADER_SIZE];
    struct wav_riff riff;
    struct wav_fmt fmt;
    struct wav_data data;
}
void read_header(FILE *fp, union header_data *file_bytes, char *file_name);
void print_header_data(union header_data *file_bytes);
void change_volume(wav *wh, float scale);
