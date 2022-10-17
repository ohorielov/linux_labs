#include <stdio.h>
#include "wav.h"
char *filename;
int main ( int args, char* argv[]){

    filename = (char*) malloc(sizeof(char) * 1024);
    // get filename from command line
    if (args < 2) {
        printf("No wave file specified\n");
        exit(1);
    }

    strcat(filename, argv[1]);

    WAV_HEADER* header = openFile(filename);


    return 0;

}