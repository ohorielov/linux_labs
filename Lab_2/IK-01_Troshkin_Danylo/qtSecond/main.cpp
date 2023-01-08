#include <QCoreApplication>
#include <stdio.h>
#include <stdlib.h>
#include "huffman.h"
#include <iostream>
#include <vector>
#include <map>
#include <list>
#include <string>
#include <fstream>
using namespace std;

int main(void)
{

    /*
    std::ofstream writeEncode("C://3_encoded.txt");
    string a = "hello";
    string b = "world";
    writeEncode<<a<<endl;
    writeEncode<<b;

    */
    int length;
        char* buffer;

        ifstream encodeFile;
        encodeFile.open("C://non_compressed_text.txt", ios::binary);

        // get length of file:
        encodeFile.seekg(0, ios::end);
        length = encodeFile.tellg();
        encodeFile.seekg(0, ios::beg);

        // allocate memory:
        buffer = new char[length];

        // read data as a block:
        encodeFile.read(buffer, length);
        encodeFile.close();

        cout.write(buffer, length);


        //We build the tree depending on the string
        htTree *codeTree = buildTree(buffer);
        //We build the table depending on the Huffman tree
        hlTable *codeTable = buildTable(codeTree);

        //We encode using the Huffman table
        encode(codeTable, buffer);
        //We decode using the Huffman tree
        //We can decode string that only use symbols from the initial string

        ifstream decodeFile;
        decodeFile.open("C://compressed_text.txt", ios::binary);

        // get length of file:
        decodeFile.seekg(0, ios::end);
        length = decodeFile.tellg();
        decodeFile.seekg(0, ios::beg);

        // allocate memory:
        char* bufferDecode;
        bufferDecode = new char[length];

        // read data as a block:
        decodeFile.read(bufferDecode, length);
        decodeFile.close();

        decode(codeTree,bufferDecode);
        //Output : 0011 1110 1011 0001 0010 1010 1100 1111 1000 1001
        delete[] buffer;
        delete[] bufferDecode;
        return 0;
}
