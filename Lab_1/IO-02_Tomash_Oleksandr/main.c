#include "header.h"

int read_wav();
int out_wav();

int main(){
    struct wav puppets;
    read_wav(&puppets);
    out_wav(&puppets);
    return 0;
}