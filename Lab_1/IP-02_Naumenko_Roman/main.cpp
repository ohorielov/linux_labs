#include <iostream>
#include "FileReader.h"

int main()
{
    FileReader* fr = FileReader::GetInstance();

    fr->ReadFile("somefile.wav");

    return 0;
}