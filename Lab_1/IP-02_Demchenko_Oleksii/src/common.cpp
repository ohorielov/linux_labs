//
// Created by h1lary on 27.09.22.
//
#include "common.h"
#include <filesystem>

bool common::CheckIfFileExists(const std::string &fileName)
{
    const std::filesystem::path pathToFileName{fileName.c_str()};
    return !std::filesystem::exists(pathToFileName);
}