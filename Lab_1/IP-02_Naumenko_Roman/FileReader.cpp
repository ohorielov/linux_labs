#include "FileReader.h"

FileReader* FileReader::staticInstance = nullptr;

FileReader::FileReader()
{};

FileReader* FileReader::GetInstance()
{
    if(staticInstance == nullptr)
    {
        staticInstance = new FileReader;
    }
    return staticInstance;
}

void FileReader::ReadFile(const std::string& fileName)
{
    std::cout << "Started reading file: " << fileName << std::endl;
}