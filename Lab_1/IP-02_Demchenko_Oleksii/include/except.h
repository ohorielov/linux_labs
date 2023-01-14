//
// Created by h1lary on 25.09.22.
//
#include <exception>
#include <sstream>
#include <string>

class pretty_expection : public std::exception
{
    const std::string description;

public:
    explicit pretty_expection(const std::string &error)
        : description(error)
    {
    }
    [[nodiscard]] const char *what() const noexcept override
    {
        return description.c_str();
    }
};
