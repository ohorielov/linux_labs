#pragma once
using namespace std;
struct node {
	char ch;
	int amount;
	node* next;
	node* left = NULL;
	node* right = NULL;
};

class letters_list {
public:
	node* head = NULL;
	int letters_amount = 0;
	void add_node(char c);
	void print_list();
	void sort_list();
	node* transform(node* head);
};

