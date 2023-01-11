#include <iostream>
#include <vector>
#include <list>
#include <map>
#include <fstream>
using namespace std;

vector<bool> code;
map<char, vector<bool> > table;


class Node {

	public:
		int a;
		char c;
		Node* left, * right;

		Node() {};

		Node(Node* L, Node* R) {
			left = L;
			right = R;
			a = L->a + R->a;
		}
};

struct MyCompare {
	bool operator()(Node* l, Node* r) const {
		return l->a < r->a;
	}
};



void BuildTable(Node* root) {
	if (root->left != NULL) {
		code.push_back(0);
		BuildTable(root->left);
	}

	if (root->right != NULL) {
		code.push_back(1);
		BuildTable(root->right);
	}

	if (root->c) table[root->c] = code;

	code.pop_back();

};



int main (){
	
	

	ifstream f("non_compressed_text.txt");
	
	map<char, int> m;

	while (!f.eof()){
		char c;
		c = f.get();
		m[c]++;
	}

	list<Node*> t;

	map<char, int>::iterator i;

	for (i = m.begin(); i != m.end(); ++i) {
		Node *p = new Node;
		p->c = i->first;
		p->a = i->second;
		t.push_back(p);
	}
	

	while (t.size()!=1){
		t.sort(MyCompare());

		Node* SonL = t.front();
		t.pop_front();
		Node* SonR = t.front();
		t.pop_front();

		Node *parent = new Node(SonL, SonR);
		t.push_back(parent);
	}

	Node* root = t.front();

	BuildTable(root);

	f.clear();
	f.seekg(0);

	ofstream g("output.bin");

	int count = 0; char buf = 0;

	while (!f.eof()) {
		char c;
		c = f.get();
		vector<bool> x = table[c];

		for (int n = 0; n < x.size(); n++) {
			
			buf = buf | x[n]<<(7 - count);
			count++;
			if (count==8){
				count=0;
				g<<buf;
				buf=0;
			}
		}
	}
	g.close();
	f.close();

	ifstream F("output.bin");

	Node *p = root;
	count = 0; char byte;
	byte = F.get();
	while (!F.eof()){
		bool b = byte & (1 << (7 - count) );
		if (b) p = p->right; else p = p->left;
		if (p-> left == NULL && p->right == NULL) {
			cout << p->c; p = root;
		}
		if (count == 8) { count = 0; F >> byte; }
	}

	F.close();

	return 0;
}