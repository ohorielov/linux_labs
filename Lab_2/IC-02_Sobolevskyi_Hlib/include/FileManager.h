#pragma once

#include <iostream>
#include <string.h>

class FileManager {
public:
    
    static FileManager* GetInstance() {
        if (shared == nullptr) {
            shared = new FileManager();
        }

        return shared;
    }

    std::string ReadFile(const char* filename);
    void WriteToFile(std::string data, const char* filename);
    
private:
    static FileManager* shared;
    
    FileManager() {}
};