#pragma once

#include "BinaryTree.h"
#include "PriorityQueue.h"

class Huffman {
public:
    Huffman() {}
    ~Huffman();

    void Encode(std::string inputString, const char* fileName);
    std::string Decode(const char* fileName);

private:
    BinaryTree* tree;
    std::map<char, std::string> codesTable;
};