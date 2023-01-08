#include "coder.h"

map<char,int> readForCharCount(const char* non_compressed_text_file){
    ifstream f(non_compressed_text_file, ios::in | ios::binary);
    map<char,int> m;
	
	while (!f.eof())
	{ 
        char c = f.get(); 
        m[c]++;
    }

    return m;
}

void encodeAndWriteToFile(const char* non_compresed_text_file,const char* compresed_text,map<char,vector<bool> > table){

    ifstream f(non_compresed_text_file, ios::out | ios::binary);
	ofstream g(compresed_text, ios::out | ios::binary);
    	
    int count=0; char buf=0;
    while (!f.eof())
    {
        char c = f.get();
        vector<bool> x = table[c];
        for(int n=0; n<x.size(); n++)
        {
            buf = buf | x[n]<<(7-count);   
            count++;   
            if (count==8) 
            { 
                count=0;   
                g<<buf; 
                buf=0; 
            } 
        }
    }
    f.close();
	g.close();
}

void decodeAndWriteToFile (const char* compresed_text_file,const char* output_file,Node *root){

	ifstream IN(compresed_text_file, ios::in | ios::binary);
	ofstream OUT(output_file, ios::out | ios::binary);

	Node *p = root;
	int count=0; char byte; 
	byte = IN.get();
	while(!IN.eof())
	{
        bool b = byte & (1 << (7-count) ) ; 
		if (b) 
            p=p->right; 
        else 
            p=p->left;
		if (p->left==NULL && p->right==NULL) 
        {
            OUT<<p->c;
            p=root;
        }  
		count++;
		if (count==8) 
        {
            count=0; 
            byte = IN.get();
        }
	}
	OUT.close();
	IN.close();	
}

void compareTwoFiles (const char* first_file,const char* second_file){
    ifstream FF(first_file, ios::in | ios::binary);
    ifstream SF(second_file, ios::in | ios::binary);
    char ch1, ch2;
    bool result = true;
    while (!SF.eof()) {
        SF.get(ch1);
        FF.get(ch2);
        if (ch1 != ch2) {
            result = false;
            break;
        }
    }
    if(!(FF.eof()&&SF.eof())) 
            result = false;
    if (result)
        cout << "*Files are equal " << endl;
    else
        cout << "*Files are not equal " << endl;

    SF.close();
    FF.close();
}