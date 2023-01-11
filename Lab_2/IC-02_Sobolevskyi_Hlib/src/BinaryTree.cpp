#include "../include/BinaryTree.h"

BinaryTree::BinaryTree(PriorityQueue* queue)
{
    BinaryTreeNode* tNode = nullptr;

    while (queue->GetSize() > 1) {
        PQueueNode* node1 = queue->Pop();
        PQueueNode* node2 = queue->Pop();
        
        tNode = new BinaryTreeNode('\0', node1->priority + node2->priority);

        if (BinaryTreeNode* n1 = dynamic_cast<BinaryTreeNode*>(node1))
            tNode->left = n1;
        else
        {
            tNode->left = new BinaryTreeNode(node1->ch, node1->priority);
            delete node1;
        }
            

        if (BinaryTreeNode* n2 = dynamic_cast<BinaryTreeNode*>(node2))
            tNode->right = n2;
        else
        {
            tNode->right = new BinaryTreeNode(node2->ch, node2->priority);
            delete node2;
        }
        
        queue->Push(tNode);
    }

    this->root = tNode;
}

//Print
void BinaryTree::Print()
{
    if (this->root)
        Print(this->root);
    else
        std::cout << "Root is nullptr" << std::endl;
}

void BinaryTree::Print(BinaryTreeNode* node)
{
    if (node->left)
        Print(node->left);
    if (node->right)
        Print(node->right);

    if (node->ch != '\0')
        std::cout << node->ch << ": " << node->priority << std::endl;
}

//Codes
void BinaryTree::FillCodes(std::map<char, std::string>& codesTable)
{
    FillCodes(this->root, "", codesTable);
}
 
void BinaryTree::FillCodes(BinaryTreeNode* node, std::string code, std::map<char, std::string>& codesTable)
{
    if (node == NULL)
        return;
    
    if (!node->left && !node->right)
    {
        // std::cout << code << std::endl;
        codesTable.emplace(node->ch, code);
    }
    else
    {
        FillCodes(node->left, code + "0", codesTable);
        FillCodes(node->right, code + "1", codesTable);
    }
}

std::string BinaryTree::ValueForCode(std::string fullCode)
{
    std::string result = "";
    BinaryTreeNode* node = this->root;
    for (const char& c: fullCode)
    {
        if (c == '0')
            node = node->left;
        else if (c == '1')
            node = node->right;

        if (node->ch != '\0')
        {
            result += node->ch;
            node = this->root;
        }
    }

    return result;
}

//Deinit
BinaryTree::~BinaryTree()
{
    if (this->root)
        DeleteNode(this->root);
}

void BinaryTree::DeleteNode(BinaryTreeNode* node)
{
    if (this->root->left)
        DeleteNode(this->root->left);

    if (this->root->right)
        DeleteNode(this->root->right);

    delete node;
}