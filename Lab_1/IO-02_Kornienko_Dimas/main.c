

#include "stdlib.h"
#include "stdio.h"
#include "wav_processor.h"

int main(void) {
	wav_header *header = malloc(sizeof *header);
	int16_t *data = malloc(sizeof *data);
	load_wav("../Master Of Puppets.wav", header, &data);
	//structure_wav(header);
	adjust_wav(header, data, -0.3);
	write_wav("./Master Of Puppets (-3дБ)", header, data);
    adjust_wav(header, data, 0.6);
	write_wav("./Master Of Puppets (+3дБ)", header, data);
    free(header);
	free(data);
	return 0;
}
