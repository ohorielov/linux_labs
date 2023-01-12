#include <iostream>
#include "table.h" 
#include "letters_list.h" 
using namespace std;

void h_table::fill_table(node* root, string code) {
	if (root->left == NULL && root->right == NULL) {
		h_row* current = new h_row();
		current->ch = root->ch;
		current->code = code;
		
		if (head == NULL) {
			head = current;
		}
		else {
			h_row* temp = head;
			while (temp->next != NULL) {
				temp = temp->next;
			}
			temp->next = current;
		}
		


	}
	else {
		if (root->left != NULL) {
			fill_table(root->left, code += '0');
		}
		if (root->right != NULL) {
			fill_table(root->right, code += '1');
		}
	}

}
void h_table::print_table() {
	h_row* temp = head;
	while (temp) {
		cout << temp->ch << " - " << temp->code << endl;
		temp = temp->next;
	}
}

string h_table::getCode(char c) {
	h_row* temp = head;
	while (temp && c!=temp->ch) {
		temp = temp->next;
	}
	return temp->code;
}

char h_table::getChar(string c) {
	h_row* temp = head;
	while (temp && c != temp->code) {
		temp = temp->next;
	}
	return temp->ch;
}