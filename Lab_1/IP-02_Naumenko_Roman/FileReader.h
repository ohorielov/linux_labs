#include <iostream>

class FileReader
{
private:
    FileReader();
public:
    static FileReader* GetInstance();
    void ReadFile(const std::string& fileName);

private:
    static FileReader* staticInstance;
};