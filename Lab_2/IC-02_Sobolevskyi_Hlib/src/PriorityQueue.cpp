#include "../include/PriorityQueue.h"
#include <iostream>

PriorityQueue::PriorityQueue(const int* inputArr, int size) {
    for (int i = 0; i < size; i++)
        if (inputArr[i] != 0)
            Push(new PQueueNode((unsigned char)i, inputArr[i]));
}

void PriorityQueue::Push(PQueueNode *node)
{
    if (first)
    {
        PQueueNode* iter = first;

        if (iter->priority >= node->priority) 
        {
            InsertAtFirst(node);
            return;
        }

        while (iter->next != nullptr)
        {
            if (iter->next->priority >= node->priority)
            {
                InsertNodeAfter(node, iter);
                return;
            }

            iter = iter->next;
        }

        iter->next = node;
    }
    else { first = node; }

    this->size++;
}

PQueueNode* PriorityQueue::Pop()
{
    if (!this->first)
        return nullptr;
    
    PQueueNode* node = this->first;
    this->first = node->next;

    this->size--;

    node->next = nullptr;
    return node;
}

void PriorityQueue::InsertNodeAfter(PQueueNode* node, PQueueNode* afterNode)
{
    PQueueNode* temp = afterNode->next;
    afterNode->next = node;
    node->next = temp;

    this->size++;
}

void PriorityQueue::InsertAtFirst(PQueueNode* node)
{
    node->next = this->first;
    this->first = node;
    
    this->size++;
}

void PriorityQueue::Print()
{
    PQueueNode* iter = this->first;

    while (iter != nullptr)
    {
        std::cout << iter->ch << " " << iter->priority << std::endl;
        iter = iter->next;
    }
}

PriorityQueue::~PriorityQueue()
{
    PQueueNode* node = this->first;
    while (node != nullptr)
    {
        PQueueNode* temp = node;
        node = node->next;
        delete temp;    
    }
}

