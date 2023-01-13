#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <iterator>
#include <algorithm>
#include <queue>
#define MAX_TREE_HT 256 

#define SPACE_SYMBOL "__"
#define NEW_LINE_SYMBOL "___"

using namespace std;

struct MinHeapNode 
{ 
    char data;          
    int freq;           
    MinHeapNode *left, *right; 
  
    MinHeapNode(char data, int freq) 
    { 
        left = right = NULL; 
        this->data = data; 
        this->freq = freq; 
    } 
}; 
struct compare 
{ 
    bool operator()(MinHeapNode* l, MinHeapNode* r) 
    { 
        return (l->freq > r->freq); 
    } 
}; 
using HeapPriorityQueue = priority_queue<MinHeapNode*, vector<MinHeapNode*>, compare>;

void printMinHeapNode(MinHeapNode* root) {
    if (root == NULL) {
        return;
    }
    cout << root->data << " " << root->freq << endl;
    printMinHeapNode(root->left);
    printMinHeapNode(root->right);
}

struct HeapNodeSerialize {
    char data;
    int freq;
    int leftIndex = -1;
    int rightIndex = -1;
};
vector<MinHeapNode*> getNodesVector (MinHeapNode* root) {
    vector<MinHeapNode*> nodes;
    if (root == NULL) {
        return nodes;
    }
    nodes.push_back(root);
    vector<MinHeapNode*> leftNodes = getNodesVector(root->left);
    vector<MinHeapNode*> rightNodes = getNodesVector(root->right);
    nodes.insert(nodes.end(), leftNodes.begin(), leftNodes.end());
    nodes.insert(nodes.end(), rightNodes.begin(), rightNodes.end());
    return nodes;
}
vector<HeapNodeSerialize> heapNodeSerialize (vector<MinHeapNode*> nodesVector) {
    vector<HeapNodeSerialize> nodes;
    for (int i = 0; i < nodesVector.size(); i++) {
        HeapNodeSerialize node;
        node.data = nodesVector[i]->data;
        node.freq = nodesVector[i]->freq;
        if (nodesVector[i]->left != NULL) {
            node.leftIndex = find(nodesVector.begin(), nodesVector.end(), nodesVector[i]->left) - nodesVector.begin();
        }
        if (nodesVector[i]->right != NULL) {
            node.rightIndex = find(nodesVector.begin(), nodesVector.end(), nodesVector[i]->right) - nodesVector.begin();
        }
        nodes.push_back(node);
    }
    return nodes;
}
vector<MinHeapNode*> heapNodeDeserialize (vector<HeapNodeSerialize> nodes) {
    vector<MinHeapNode*> nodesVector;
    for (int i = 0; i < nodes.size(); i++) {
        MinHeapNode* node = new MinHeapNode(nodes[i].data, nodes[i].freq);
        nodesVector.push_back(node);
    }
    for (int i = 0; i < nodes.size(); i++) {
        if (nodes[i].leftIndex != -1) {
            nodesVector[i]->left = nodesVector[nodes[i].leftIndex];
        }
        if (nodes[i].rightIndex != -1) {
            nodesVector[i]->right = nodesVector[nodes[i].rightIndex];
        }
    }
    return nodesVector;
}
HeapPriorityQueue getNodesPriorityQueue (vector<MinHeapNode*> nodesVector) {
    HeapPriorityQueue nodes;
    for (int i = 0; i < nodesVector.size(); i++) {
        nodes.push(nodesVector[i]);
    }
    return nodes;
}
MinHeapNode* findRoot (vector<MinHeapNode*> nodesVector) {
    for (MinHeapNode* node : nodesVector) {
        bool isRoot = true;
        for(MinHeapNode *target: nodesVector){
            if(target->left == node || target->right == node)
                isRoot == false;
        }

        if(isRoot)
            return node;
    }
    return NULL;
}
pair<vector<MinHeapNode*>, string> deserialize ( string fileName) {
    ifstream file;
    file.open(fileName);
    vector<HeapNodeSerialize> nodesSerialize;
    size_t size;
    file >> size;
    for (int i = 0; i < size; i++) {
        HeapNodeSerialize node;
        string data;
        file >> data;
        if (data == SPACE_SYMBOL) {
            node.data = ' ';
        } else if (data == NEW_LINE_SYMBOL) {
            node.data = '\n';
        } else {
            node.data = data[0];
        }
        file >> node.freq >> node.leftIndex >> node.rightIndex;
        nodesSerialize.push_back(node);
    }
    string encodedText;
    file >> encodedText;
    file.close();
    vector<MinHeapNode*> nodesVector = heapNodeDeserialize(nodesSerialize);
    return {nodesVector, encodedText};
}

void serialize (MinHeapNode* root, string fileName, string encodedText) {
    vector<MinHeapNode*> nodesVector = getNodesVector(root);
    vector<HeapNodeSerialize> nodes = heapNodeSerialize(nodesVector);
    ofstream file;
    file.open(fileName);
    file << nodes.size() << endl;
    for (int i = 0; i < nodes.size(); i++) {
        if (nodes[i].data == ' ') {
            file << SPACE_SYMBOL;
        } else if (nodes[i].data == '\n') {
            file << NEW_LINE_SYMBOL;
        } else {
            file << nodes[i].data;
        }
        file << " " << nodes[i].freq << " ";
        file << nodes[i].leftIndex << " " << nodes[i].rightIndex << endl;
    }
    file << encodedText << endl;
    file.close();
}
void printCodes(struct MinHeapNode* root, string str) 
{ 
    if (!root) 
        return; 
    if (root->data != '$') 
        cout << root->data << ": " << str << "\n"; 
    printCodes(root->left, str + "0"); 
    printCodes(root->right, str + "1"); 
} 
 map<char, int> calcFreq(string str, int n) 
{ 
    map<char, int> freq; 

    for (int i=0; i<str.size(); i++) 
        freq[str[i]]++; 

    return freq;
} 
void storeCodes(struct MinHeapNode* root, string str, map<char, string>* codes) 
{ 
    if (root==NULL) 
        return; 
    if (root->data != '$') 
        (*codes)[root->data]=str; 
    storeCodes(root->left, str + "0", codes); 
    storeCodes(root->right, str + "1", codes); 
} 
  
pair<string, HeapPriorityQueue> HuffmanCodes(string data) 
{ 
    map<char, int> freq = calcFreq(data, data.length());
    HeapPriorityQueue minHeap; 

    struct MinHeapNode *left, *right, *top; 
    for (map<char, int>::iterator v=freq.begin(); v!=freq.end(); v++) 
        minHeap.push(new MinHeapNode(v->first, v->second)); 
    while (minHeap.size() != 1) 
    { 
        left = minHeap.top(); 
        minHeap.pop(); 
        right = minHeap.top(); 
        minHeap.pop(); 
        top = new MinHeapNode('$', left->freq + right->freq); 
        top->left = left; 
        top->right = right; 
        minHeap.push(top); 
    } 
    map<char, string> codes; 

    storeCodes(minHeap.top(), "", &codes); 
    
    string encodedString = "";
    for (auto i: data) 
        encodedString+=codes[i]; 
    return { encodedString, minHeap};
} 
string decode_file(struct MinHeapNode* root, string s) 
{ 
    string ans = ""; 
    struct MinHeapNode* curr = root; 
    for (int i=0;i<s.size();i++) 
    { 
        if (s[i] == '0') 
           curr = curr->left; 
        else
           curr = curr->right; 
  
        if (curr->left==NULL && curr->right==NULL) 
        { 
            ans += curr->data; 
            curr = root; 
        } 
    } 
    return ans+'\0'; 
} 

string readInputFile (string fileName) {
    ifstream file;
    file.open(fileName);
    string str;
    string line;
    while (getline(file, line, '\0')) {
        str += line;
    }
    return str;
}

int main () {
    string fileName = "../non_compressed_text.txt";
    string newFileName = "compressed_text.txt";

    string str = readInputFile(fileName);
;

    auto [encodedString, minHeap] = HuffmanCodes(str); 
  

    serialize(minHeap.top(), newFileName, encodedString);
    auto [nodeVector, encodedText] = deserialize(newFileName);
    MinHeapNode* root = findRoot(nodeVector);

    string decodedString = decode_file(root, encodedText); 
    cout << "\nDecoded Huffman Data:\n" << decodedString << endl; 
    return 0; 
}