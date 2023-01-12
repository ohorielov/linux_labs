#include <string>
#include "tree.h" 
using namespace std;

struct h_row {
	string code;
	char ch;
	h_row* next;
};

class h_table {
public:
	h_row* head = NULL;
	void fill_table(node* root, string code);
	void print_table();
	string getCode(char c);
	char getChar(string c);
};