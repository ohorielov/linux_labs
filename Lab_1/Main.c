#include "wave.h"

int main(){
    struct WavHeader wav_header r = {}
    FILE *file_input = 1 fopen(input, "rb");
    read_header (file_input, &wav_header);
    print_header_data(&wav_header);
    change_volume(&wav_header, VOLUME);
    return 0;

}
