#include <stdio.h>
int main(int argc, char *argv[]){
    FILE *fin = fopen("input.wav", "r");
    FILE *fout = fopen("final.wav", "w");
    int counter = 0;
    uint16_t data;
    while(fread(&data, 2, 1, fin)){
        data = counter++ < 22 ? data : data * 2.0;
        fwrite(&data, 2, 1, fout);
    }
    fclose(fin);
    fclose(fout);
    return 0;
}
