#include "wav.h"

void parse_wav(int filedesc, struct Wav* wh) {
	read(filedesc, wh, WAV_HEADER_SIZE_BYTES);

	wh->data = malloc(wh->size_bytes);
    read(filedesc, wh->data, wh->size_bytes);

	close(filedesc);
}

void write_wav(const char *file_name, struct Wav *wh) {
	int filedesc = creat(file_name, S_IRUSR | S_IWUSR);
	int file_size = wh->wav_size + 8;

	write(filedesc, wh, WAV_HEADER_SIZE_BYTES);
	write(filedesc, wh->data, file_size - WAV_HEADER_SIZE_BYTES);

	close(filedesc);
}

void change_volume(struct Wav *wh, float scale) {
	for (int i = 0; i < wh->size_bytes / sizeof(wh->sample_alignment); i++) {
		int16_t *data = (int16_t *) wh->data;
		float scaled = data[i] * scale;

		if (scaled >= INT16_MAX) {
			data[i] = INT16_MAX;
		} else if (scaled <= INT16_MIN) {
			data[i] = INT16_MIN;
		} else {
			data[i] = (int16_t)scaled;
		}
	}
}

void print_wav_header(struct Wav *wh) {
	printf("--- RIFF chunk ---\n");
    printf("Riff: %d\n", wh->riff_header);
	printf("Size: %d\n", wh->wav_size);
	printf("Format: %d\n", wh->wave_header);

	printf("\n--- FMT chunk ---\n");
	printf("Subchunk 1 id: %d\n", wh->fmt_header);
	printf("Subchunk 1 size: %d\n", wh->chunk_size);
	printf("Audio format: %d\n", wh->audio_format);
	printf("Num channels: %d\n", wh->num_channels);
	printf("Sample rate: %d\n", wh->sample_rate);
	printf("Byte rate: %d\n", wh->byte_rate);
	printf("Block align: %d\n", wh->sample_alignment);
	printf("Bits per sample: %d\n", wh->bit_depth);

	printf("\n--- DATA chunk ---\n");
	printf("Subchunk 2 ID: %d\n", wh->data_header);
	printf("Subchunk 2 size: %d\n", wh->size_bytes);
}
