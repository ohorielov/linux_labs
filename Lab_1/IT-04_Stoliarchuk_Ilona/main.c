#include "process.h"

int main(){
	struct WavHeader wav = {};
	read("../Master Of Puppets.wav", &wav);
	print("../Master Of Puppets.wav", &wav);
	edit(-3, &wav);
	write("new.wav", &wav);
	return 0;
}
