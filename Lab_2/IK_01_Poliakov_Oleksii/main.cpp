#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

vector<string> readFile (string fileName) {
    vector<string> data;
    fstream fileStream;
    fileStream.open(fileName, ios::in);
    if (!fileStream.is_open()) {
        throw logic_error("File can not be opened");
    }
    string line;
    while (getline(fileStream, line)) {
        data.push_back(line);
    }
    fileStream.close();
    return data;
}

void writeFile (string fileName, vector<string> data) {
    fstream fileStream;
    fileStream.open(fileName, ios::out);
    if (!fileStream.is_open()) {
        throw logic_error("File can not be opened");
    }
    for (string line : data) {
        fileStream << line << endl;
    }
    fileStream.close();
}

int main () {
    string fileName = "../non_compressed_text.txt";
    vector<string> data = readFile(fileName);
    string newFileName = "new.txt";
    writeFile(newFileName, data);
}