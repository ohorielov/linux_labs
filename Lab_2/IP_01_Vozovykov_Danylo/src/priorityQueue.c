#include "priorityQueue.h"

PriorityQueue* createPriorityQueue() {
	PriorityQueue* pq = (PriorityQueue*)malloc(sizeof(PriorityQueue));
	pq->head = NULL;
	return pq;
}

void enqueue(PriorityQueue* pq, TreeNode* treeNode, int priority)
{
    PQNode* newNode = (PQNode*)malloc(sizeof(PQNode));
    newNode->treeNode = treeNode;
    newNode->priority = priority;
    newNode->next = NULL;

    if (pq->head == NULL || priority < pq->head->priority)
    {
    	newNode->next = pq->head;
    	pq->head = newNode;
    }
    else
    {
		PQNode* current = pq->head;
		while (current->next != NULL && current->next->priority <= priority)
		{
			current = current->next;
		}
		newNode->next = current->next;
		current->next = newNode;
	}
}

TreeNode* dequeue(PriorityQueue* pq)
{

	if (pq->head == NULL)
	{
    	return NULL;
    }

    PQNode* current = pq->head;
    pq->head = current->next;
    TreeNode* treeNode = current->treeNode;
    free(current);
    return treeNode;
}
