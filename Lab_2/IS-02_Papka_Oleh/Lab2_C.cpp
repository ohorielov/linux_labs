#include <iostream>
#include <fstream>
#include <sstream>
#include "Huffman.h"

void ReadFromFile(std::string& text, const std::string& filename)
{
    std::stringstream stream;
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cout << "Error reading file" << std::endl;
        return;
    }

    stream << file.rdbuf();
    file.close();
    text = stream.str();
}
void WriteToFile(const std::string& text)
{
    std::ofstream file("compressed_text.txt");

    if (!file.is_open()) {
        std::cout << "Error reading file" << std::endl;
        return;
    }

    file << text;
    file.close();
}

int main()
{
    Huffman h;
    std::string str;
    ReadFromFile(str, "non_compressed_text.txt");
   
    WriteToFile(h.Encode(str));
    
    std::string encodedstring;
    ReadFromFile(encodedstring, "compressed_text.txt");
    std::string decodedString = h.Decode(encodedstring);

    std::cout << "\n" << decodedString << "\n" << std::endl;

    if (!str.compare(decodedString))
        std::cout << "String are the same" << std::endl;
    else
        std::cout << "String are not the same" << std::endl;
    

}