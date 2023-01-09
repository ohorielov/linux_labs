#include "my_lib.h"

int main(){
	printf("Welcome!\n");
	if(read_wav("Master Of Puppets.wav")){
		printf("Can`t find file Master Of Puppets.wav");
	}
	return 0;
}
