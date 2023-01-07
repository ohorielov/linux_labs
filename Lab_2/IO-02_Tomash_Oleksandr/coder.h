#include <iostream>
#include <vector>
#include <map>
#include <list>
#include <fstream>
using namespace std;


class Node
{
	public:
    int a;
    char c;
    Node *left, *right;
    Node()
    {
        left=right=NULL;
    }
    Node(Node *L, Node *R) 
    {
        left =  L;
	    right = R;
	    a = L->a + R->a;  
    }
};

struct MyCompare
{
    bool operator()(const Node* l, const Node* r) const
    { 
        return l->a < r->a; 
    }
}; 

map<char,int> readForCharCount(const char* non_compressed_text_file);

void encodeAndWriteToFile(const char* non_compresed_text_file,const char* compresed_text,map<char,vector<bool> > table);

void decodeAndWriteToFile (const char* compresed_text_file,const char* output_file,Node *root);

void compareTwoFiles (const char* first_file,const char* second_file);