#include "wav.h"

#define INPUT_WAV "../Master Of Puppets.wav"
#define OUTPUT_WAV "../m-output.wav"
#define SCALE_FACTOR 0.2

int main() {
    struct Wav wav = {};

	int filedesc = open(INPUT_WAV, O_RDWR);
	if (filedesc == -1) return -1;

	parse_wav(filedesc, &wav);
	print_wav_header(&wav);

	change_volume(&wav, SCALE_FACTOR);

	write_wav(OUTPUT_WAV, &wav);

    return 0;
}
