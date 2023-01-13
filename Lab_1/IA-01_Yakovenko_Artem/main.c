#include "wav_header.h"

int wav_reader();
int wav_output();

int main(){
struct wav song;
wav_reader(&song);
wav_output(&song);
return 0;
}

