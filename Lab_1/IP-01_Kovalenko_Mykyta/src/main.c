#include "stdlib.h"
#include "stdio.h"
#include "wav_processor.h"

int main(void) {
	wav_header *header = malloc(sizeof *header);
	load_wav("../Master Of Puppets.wav", header);
	dump_wav(header);
	adjust_wav(header, 0.75);
	write_wav("../build/Master Of Puppets - Remastered.wav", header);
	free(header->data);
	free(header);
	return 0;
}
