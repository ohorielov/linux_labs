#include <iostream>
#include <string>
#include "WavHandler.h"
#include "Macroses.h"

int main(int argc, char** argv)
{
    if (argc < 4)
    {
        InfoLog("Some arguments are not specified.");
        InfoLog("Example: ./main inputFile.txt outputFile.txt 0.4");
        return -1;
    }

    float factor = std::stof(argv[3]);

    if (factor > 1.0f || factor <= 0.0f)
    {
        DebugLog("Volume scale factor value must be in range of (0, 1].");
        return -1;
    }

    return WavHandler{}.ScaleVolume(argv[1], argv[2], factor);
}