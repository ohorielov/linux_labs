#include "wav.h"
#include <iostream>
#include <wavreader.h>

namespace
{
void Process(const std::string &filePath)
{
    WAVReader wavReader{filePath};
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
