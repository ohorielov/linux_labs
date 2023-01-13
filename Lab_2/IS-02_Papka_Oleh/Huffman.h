#pragma once
#include <iostream>
#include "TreeNode.h"
#include <map>
#include <unordered_map>
#include <queue>
#include <vector>
#include <string>

class Huffman
{
private:
	class ComparisonFunctor
	{
	public:
		bool operator()(TreeNode* left, TreeNode* right)
		{
			return left->frequency > right->frequency;
		}
	};
	std::priority_queue < TreeNode*, std::vector<TreeNode*>, ComparisonFunctor> p_queue;
	std::unordered_map<char, int> frequency;
	std::map<char, std::string> huffmanCodes;
public:
	std::string Encode(const std::string& str);
	void CalculateFrequency(const std::string& str);
	void StoreCodes(TreeNode* root, const std::string& str);
	void PrintCodes(TreeNode* root, std::string str);
	std::string Decode(std::string encodedString);
};