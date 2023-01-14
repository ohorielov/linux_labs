#include <iostream>
#include <string>
#include <queue>
#include <unordered_map>
#include <fstream>
#include <sstream>
#include <cstring>

#define INPUT_FILE "../non_compressed_text.txt"
#define COMPRESSED_FILE "compressed_text.txt"
#define UNCOMPRESSED_FILE "uncompressed_text.txt"

using namespace std;

struct Node {
    char ch;
    int freq;
    Node *left, *right;
};

Node *getNode(char ch, int freq, Node *left, Node *right) {
    Node *node = new Node();

    node->ch = ch;
    node->freq = freq;
    node->left = left;
    node->right = right;

    return node;
}

struct comp {
    bool operator()(Node *l, Node *r) {
        return l->freq > r->freq;
    }
};

void encode(Node *root, string str, unordered_map<char, string> &huffmanCode) {
    if (root == nullptr)
        return;

    if (!root->left && !root->right) {
        huffmanCode[root->ch] = str;
    }

    encode(root->left, str + "0", huffmanCode);
    encode(root->right, str + "1", huffmanCode);
}

void decode(Node *root, int &index, string str, ofstream &fout_uncomp) {
    if (root == nullptr) {
        return;
    }

    if (!root->left && !root->right) {
        fout_uncomp << root->ch;
        return;
    }

    index++;

    if (str[index] == '0')
        decode(root->left, index, str, fout_uncomp);
    else
        decode(root->right, index, str, fout_uncomp);
}

void buildHuffmanTree(string text) {
    unordered_map<char, int> freq;
    for (char ch: text) {
        freq[ch]++;
    }

    priority_queue<Node *, vector<Node *>, comp> pq;

    for (auto pair: freq) {
        pq.push(getNode(pair.first, pair.second, nullptr, nullptr));
    }

    while (pq.size() != 1) {
        Node *left = pq.top();
        pq.pop();
        Node *right = pq.top();
        pq.pop();

        int freq_sum = left->freq + right->freq;
        pq.push(getNode('\0', freq_sum, left, right));
    }

    Node *root = pq.top();

    unordered_map<char, string> huffmanCode;
    encode(root, "", huffmanCode);

    cout << "Huffman Codes are :\n" << '\n';
    for (auto pair: huffmanCode) {
        cout << pair.first << " " << pair.second << '\n';
    }

    ofstream fout(COMPRESSED_FILE);
    string str = "";
    for (char ch: text) {
        fout << huffmanCode[ch];
        str += huffmanCode[ch];
    }
    fout.close();
    cout << "\nEncoded string is :\n" << str << '\n';

    ofstream fout_uncomp(UNCOMPRESSED_FILE);
    int index = -1;
    while (index < (int) str.size() - 2) {
        decode(root, index, str, fout_uncomp);
    }
    fout_uncomp.close();
}

void compare_files(string filename1, string filename2) {
    ifstream fin1(filename1);
    ifstream fin2(filename2);

    stringstream ss1, ss2;
    ss1 << fin1.rdbuf();
    ss2 << fin2.rdbuf();

    int n = memcmp(ss1.str().c_str(), ss2.str().c_str(), ss1.str().size());
    if (n > 0) {
        cout << filename1 << " is greater than " << filename2 << endl;
    } else if (n < 0) {
        cout << filename1 << " is less than " << filename2 << endl;
    } else {
        cout << filename1 << " is the same as " << filename2 << endl;
    }
    fin1.close();
    fin2.close();
}

int main() {
    ifstream fin(INPUT_FILE);
    stringstream ss;
    ss << fin.rdbuf();
    fin.close();

    buildHuffmanTree(ss.str());
    compare_files(INPUT_FILE, UNCOMPRESSED_FILE);

    return 0;
}
