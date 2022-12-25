#include "../include/FileManager.h"
#include <fstream>
#include <sstream>

FileManager* FileManager::shared = nullptr;

std::string FileManager::ReadFile(const char* filename) {
    std::stringstream stream;
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cout << "Can't read file" << std::endl;
        return "";
    }

    stream << file.rdbuf();
    file.close();

    return stream.str();
}

void FileManager::WriteToFile(std::string data, const char* filename) {
    std::ofstream file(filename);

    if (!file.is_open()) {
        std::cout << "Can't write to file" << std::endl;
        return;
    }

    file << data;
    file.close();
}