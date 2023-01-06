#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

int doSmth(int *num) {
    *num = 7;

    return 0;
}

int main(void) {
    int num = 6;
    doSmth(&num);

    printf("%d", num);

    return 0;
}