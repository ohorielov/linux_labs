#include "Huffman.h"

std::string Huffman::Encode(const std::string& str)
{
	TreeNode* left, *right, *top;
	std::string encodedString;
	CalculateFrequency(str);

	for (auto pair : frequency)
		p_queue.push(new TreeNode(pair.first, pair.second));

	while (p_queue.size() != 1)
	{
		left = p_queue.top();
		p_queue.pop();

		right = p_queue.top();
		p_queue.pop();

		top = new TreeNode('$', left->frequency + right->frequency);
		top->left = left;
		top->right = right;
		p_queue.push(top);
	}
	PrintCodes(p_queue.top(), "");
	StoreCodes(p_queue.top(), "");
	for (auto symbol : str)
		encodedString += huffmanCodes[symbol];
	return encodedString;
}

void Huffman::CalculateFrequency(const std::string& str)
{
	for (int i = 0; i < str.size(); i++)
		frequency[str[i]]++;
}

void Huffman::StoreCodes(TreeNode* root, const std::string& str)
{
	if (!root)
		return;
	if (root->symbol != '$')
		huffmanCodes[root->symbol] = str;
	StoreCodes(root->left, str + "0");
	StoreCodes(root->right, str + "1");
}

void Huffman::PrintCodes(TreeNode* root, std::string str)
{
	if (!root)
		return;
	if (root->symbol != '$')
		std::cout << root->symbol << ": " << str << "\n";
	PrintCodes(root->left, str + "0");
	PrintCodes(root->right, str + "1");
}

std::string Huffman::Decode(std::string encodedString)
{
	std::string result = "";
	TreeNode* curr = p_queue.top();
	for (int i = 0; i < encodedString.size(); i++) {
		if (encodedString[i] == '0')
			curr = curr->left;
		else
			curr = curr->right;

		if (curr->left == nullptr && curr->right == nullptr) 
		{
			result += curr->symbol;
			curr = p_queue.top();
		}
	}
	return result;

}

