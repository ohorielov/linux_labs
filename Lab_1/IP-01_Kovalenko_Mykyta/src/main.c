#include "stdlib.h"
#include "stdio.h"
#include "wav_processor.h"

int main(void) {
	wav_header *header = malloc(sizeof *header);
	int16_t *data = malloc(sizeof *data);
	load_wav("../Master Of Puppets.wav", header, &data);
	dump_wav(header);
	adjust_wav(header, data, 0.5);
	write_wav("../build/Master Of Puppets - Remastered.wav", header, data);
	free(header);
	free(data);
	return 0;
}
