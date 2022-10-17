#include "wav.h"

char *filename;
char *modifiedFilename;

int main ( int args, char* argv[]){

    filename = (char*) malloc(sizeof(char) * 1024);
    modifiedFilename = (char*) malloc(sizeof(char) * 1024);

    // get filename from command line
    if (args < 2) {
        printf("No wave file specified\n");
        exit(1);
    }

    strcat(filename, argv[1]);
    strcat(modifiedFilename, "Master Of Puppets Modified.wav");

    WAV_HEADER* header = openFile(filename);

    changeVolume(header, false);

    saveInNewFile(header, modifiedFilename);

    free(filename);
    free(modifiedFilename);

    return 0;
}