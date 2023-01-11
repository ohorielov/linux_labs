#include "../include/FileManager.h"
#include "../include/Huffman.h"

int main() {

    FileManager* fileManager = FileManager::GetInstance();
    std::string inputString = fileManager->ReadFile("../non_compressed_text.txt");
    // std::string inputString = "beep boop beer!";
    std::cout << inputString << std::endl;

    Huffman huffman;
    huffman.Encode(inputString, "../build/output.txt");

    std::string decodedString = huffman.Decode("../build/output.txt");
    std::cout << decodedString << std::endl;

    std::cout << inputString.compare(decodedString) << std::endl;

    return 0;
}