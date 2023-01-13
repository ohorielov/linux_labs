#include "process.h"

int main(){
	struct WavHeader wav = {};
	read("../Master Of Puppets.wav", &wav);
	print("../Master Of Puppets.wav", &wav);
	edit(0.5, &wav);
	write("new.wav", &wav);
	return 0;
}
