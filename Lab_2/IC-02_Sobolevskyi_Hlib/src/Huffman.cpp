#include "../include/Huffman.h"
#include "../include/FileManager.h"

void Huffman::Encode(std::string inputString, const char* fileName)
{
    //Filling char frequencies
    int* frequency = new int[256];
	for(int i = 0; i < 256; i++)
		frequency[i] = 0;

	for(int i=0; inputString[i] != '\0'; i++) // \n == 0 index
        frequency[(unsigned char) inputString[i]]++;

    //Filling queue with char frequencies
    PriorityQueue* queue = new PriorityQueue(frequency, 256);
    queue->Print();
    std::cout << std::endl << std::endl;

    //Queue to binary tree
    this->tree = new BinaryTree(queue);
    this->tree->Print();

    //Create codes table from tree
    this->tree->FillCodes(codesTable);
    
    //Write to file
    std::string data = "";
    for (const char& c : inputString)
        data += codesTable.at(c);

    FileManager::GetInstance()->WriteToFile(data, fileName);
}

std::string Huffman::Decode(const char* fileName)
{
    std::string data = FileManager::GetInstance()->ReadFile(fileName);
    std::cout << data << std::endl;
    if (this->tree)
        return this->tree->ValueForCode(data);

    return "\0";
}

Huffman::~Huffman()
{
    delete this->tree;
}