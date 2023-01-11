#include "wav.h"
#include "wavprocessor.h"
#include "wavreader.h"
#include <iostream>

namespace
{
void Process(const std::string &filePath)
{
    WAVReader wavReader{filePath};
    wavReader.OutputHeaderInfo();

    WAVProcessor wavProcessor{wavReader};
    wavProcessor.CopyAndChangeVolume(-0.7f);
}
}// namespace

int main()
{
    std::string filePath;
    std::cout << "input file path to wav file: ";
    getline(std::cin, filePath);

    try
    {
        Process(filePath);
    }
    catch (const std::exception &ex)
    {
        std::cout << ex.what();
    }

    return 0;
}
