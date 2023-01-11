//
// Created by h1lary on 27.09.22.
//
#include "common.h"
#include <filesystem>

namespace common
{
bool CheckIfFileExists(const std::string &fileName)
{
    const std::filesystem::path pathToFileName{fileName.c_str()};
    return !std::filesystem::exists(pathToFileName);
}

std::string GetSeparator()
{
#ifdef _WIN32
    return "\\";
#endif
#ifdef linux
    return "/";
#endif
}
}// namespace common
