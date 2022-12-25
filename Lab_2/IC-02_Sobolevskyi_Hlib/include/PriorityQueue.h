#pragma once
#include "BaseNode.h"

struct PQueueNode: BaseNode
{
    PQueueNode* next = nullptr;

    PQueueNode(char ch, int priority) : BaseNode(ch, priority) {};
    PQueueNode(BaseNode* node) : BaseNode(node) {};
};

class PriorityQueue
{
public:
    PriorityQueue(const int* inputArr, int size); //Constructor for priority array
    ~PriorityQueue();
    void Push(PQueueNode *node);
    PQueueNode* Pop();
    void Print();

    int GetSize() const { return this->size; }
    bool IsEmpty() { return this->size == 0; }

private:
    PQueueNode *first = nullptr;
    int size = 0;

    void InsertNodeAfter(PQueueNode* node, PQueueNode* afterNode);
    void InsertAtFirst(PQueueNode* node);
};