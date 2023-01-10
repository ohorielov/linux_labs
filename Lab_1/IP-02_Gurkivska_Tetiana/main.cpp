#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "wav.h"


int main()
{
    header wav;
    wav.read_data();
    wav.print_data();
    wav.change_and_safe();
}


