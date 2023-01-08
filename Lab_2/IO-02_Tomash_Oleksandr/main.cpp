#include "coder.h"


vector<bool> code;                
map<char,vector<bool> > table;    

void BuildTable(Node *root)
{	
    if (root->left!=NULL) 
    {
        code.push_back(0);
        BuildTable(root->left);
    } 
    if (root->right!=NULL)
    {
        code.push_back(1);
        BuildTable(root->right);
    }
   
    if (root->left==NULL && root->right==NULL)
        table[root->c]=code;     
    
    code.pop_back();
}

int main (int argc, char *argv[])
{
    const char *non_compresed_input {"non_compressed_text.txt"};
    const char *compesed_output {"compresed_text.txt"};
    const char *decompresed_output {"decoded_non_compresed_text.txt"};

    map<char,int> m;
    m = readForCharCount(non_compresed_input);
 
    list<Node*> t;
    for( map<char,int>::iterator itr=m.begin(); itr!=m.end(); ++itr)
    {  
        Node *p = new Node;
        p->c = itr->first;
        p->a = itr->second;
        t.push_back(p);
    }	
	
    while (t.size()!=1)
    {  
        t.sort(MyCompare());
        Node *SonL = t.front();
        t.pop_front();
        Node *SonR = t.front(); 
        t.pop_front();
        Node *parent = new Node(SonL,SonR); 
        t.push_back(parent);
    }
	
	Node *root = t.front();  

   	BuildTable(root);   
		
    encodeAndWriteToFile(non_compresed_input,compesed_output,table);

    decodeAndWriteToFile(compesed_output,decompresed_output, root);
    
    compareTwoFiles(decompresed_output,non_compresed_input);

	return 0;
}