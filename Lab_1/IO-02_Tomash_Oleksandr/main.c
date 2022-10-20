#include "header.h"

int read_wav();
int out_wav();
void print_header();

int main(){
    wav puppets;
    read_wav(&puppets);
    print_header(&puppets);
    out_wav(&puppets);
    return 0;
}