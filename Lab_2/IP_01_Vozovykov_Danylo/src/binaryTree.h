#ifndef BINARY_TREE
#define BINARY_TREE

#include <stdio.h>
#include <stdlib.h>

// A tree node that stores a character and its frequency
typedef struct TreeNode {
	char ch;
	int freq;
	struct TreeNode* left;
	struct TreeNode* right;
} TreeNode;

TreeNode* createTreeNode(char ch, int freq, TreeNode* left, TreeNode* right);
void freeTree(TreeNode* root);

#endif
