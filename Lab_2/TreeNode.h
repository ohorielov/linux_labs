#pragma once

struct TreeNode
{
	TreeNode(char symbol, int frequency) : left(nullptr), right(nullptr),
		symbol(symbol), frequency(frequency)
	{}
	TreeNode* left;
	TreeNode* right;
	char symbol;
	int frequency;
};