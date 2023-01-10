#ifndef PRIORITY_QUEUE
#define PRIORITY_QUEUE

#include<stdio.h>
#include <stdlib.h>

#include "binaryTree.h"

// A priority queue node that stores a tree node and its priority
typedef struct PQNode {
	TreeNode* treeNode;
	int priority;
	struct PQNode* next;
} PQNode;

// A priority queue that stores PQNodes in ascending order of priority
typedef struct PriorityQueue {
	PQNode* head;
} PriorityQueue;

PriorityQueue* createPriorityQueue();
void enqueue(PriorityQueue* pq, TreeNode* treeNode, int priority);
TreeNode* dequeue(PriorityQueue* pq);

#endif
