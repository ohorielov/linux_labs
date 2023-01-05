#include "utils.h"


int fileRead(FILE *fp, void *buffer, size_t len) {
    int currentByte;

    if (len == 1) {
        currentByte = fgetc(fp);
        
        *(int *)buffer = currentByte;
        if (currentByte == EOF) {
            return 0;
        } 
        return 1;
    }
    return fread(buffer, 1, len, fp);
}
