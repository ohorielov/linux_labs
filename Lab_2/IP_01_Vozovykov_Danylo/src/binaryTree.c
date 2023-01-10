#include "binaryTree.h"

// Creates a new tree node
TreeNode* createTreeNode(char ch, int freq, TreeNode* left, TreeNode* right)
{
    TreeNode* node = (TreeNode*)malloc(sizeof(TreeNode));
    node->ch = ch;
    node->freq = freq;
    node->left = left;
    node->right = right;
    return node;
}

// Frees the memory used by the tree
void freeTree(TreeNode* root) {
	if (root == NULL)
		return;

	freeTree(root->left);
	freeTree(root->right);
	free(root);
}
