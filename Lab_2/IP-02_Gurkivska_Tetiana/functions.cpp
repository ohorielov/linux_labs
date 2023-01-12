#include <string>
#include <fstream>  // Para ofstream
#include <iostream> // Para cout
#include "table.h"
#define input "../non_compressed_text.txt"
#define output "../compressed_text.txt"
#define output2 "../decodded_text.txt"
#include "letters_list.h" 
using namespace std;
void print_tree(node* root, int deep) {
    //cout << "root - " << root->ch << endl;
    if (root->left != nullptr) {
 /*       cout << "left" << endl;*/
        if (root->left != NULL) {
            node* next_step = root->left;
            print_tree(next_step, deep + 1);
        }
    }
    deep - 1;

    string d = "";
    for (int i = 0; i < deep; i++) {
        d += " ";
    }
    cout << d << root->ch << endl;
    //cout << d << deep << endl;
    if (root->right != nullptr) {
        if (root->right != NULL) {
  /*          cout << "right" << endl;*/
            node* next_step = root->right;
            print_tree(next_step, deep + 1);
        }
    }

}


string open_and_read_file() {
	string text;
	ifstream file_text;
	file_text.open(input);
	if (!file_text)
	{
		cout << "Error al abrir archivo\n";
		exit(EXIT_FAILURE);
	}
	while (!file_text.eof()) {
		string row;
		getline(file_text, row);
		text += row;
	}
	cout << "text = " << text;
	return text;

}

void create_and_write_file(string text, h_table table) {
    ofstream file(output);
    for (int i = 0; i < text.size(); i++) {
        string letter_code = table.getCode(text[i]);
        file << letter_code << " ";
    }
    file.close();
}


void decoded_text(h_table table) {
	string text;
	ifstream file_text;
	ofstream file(output2);
	file_text.open(output);
	if (!file_text)
	{
		cout << "Error al abrir archivo\n";
		exit(EXIT_FAILURE);
	}
	while (!file_text.eof()) {
		string code;
		file_text >>code;
		if (code != "") {
			char ch = table.getChar(code);
			text += ch;
			
		}
		
	}
	file_text.close();
	file << text;
	file.close();

}