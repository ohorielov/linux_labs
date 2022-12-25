#pragma once

#include "PriorityQueue.h"
#include "BaseNode.h"
#include <iostream>
#include <map>

struct BinaryTreeNode: PQueueNode
{
    BinaryTreeNode* left = nullptr;
    BinaryTreeNode* right = nullptr;

    BinaryTreeNode(BaseNode* node) : BinaryTreeNode(node->ch, node->priority) {}
    BinaryTreeNode(char ch, int priority) : PQueueNode(ch, priority) {}
};

class BinaryTree
{
public:
    BinaryTree(PriorityQueue* queue);
    ~BinaryTree();

    void AddNode(BinaryTreeNode* node);

    void Print();

    void FillCodes(std::map<char, std::string>& codesTable);
    std::string ValueForCode(std::string fullCode);
private:
    BinaryTreeNode* root = nullptr;
    void DeleteNode(BinaryTreeNode* node);

    void Print(BinaryTreeNode* node);
    
    void FillCodes(BinaryTreeNode* node, std::string str, std::map<char, std::string>& codesTable);
};