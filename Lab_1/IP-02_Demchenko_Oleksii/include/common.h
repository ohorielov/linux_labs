//
// Created by h1lary on 27.09.22.
//

#ifndef IP_02_DEMCHENKO_OLEKSII_COMMON_H
#define IP_02_DEMCHENKO_OLEKSII_COMMON_H
#include <filesystem>
#include <string>

namespace common
{
bool CheckIfFileExists(const std::string &fileName);
std::string GetSeparator();
}// namespace common

#endif//IP_02_DEMCHENKO_OLEKSII_COMMON_H
