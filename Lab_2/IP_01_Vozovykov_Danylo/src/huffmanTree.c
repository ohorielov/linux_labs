#include "huffmanTree.h"

TreeNode* buildTree(int freq[MAX_CHARS])
{
	PriorityQueue* pq = createPriorityQueue();

	for (int i = 0; i < MAX_CHARS; i++)
	{
		if (freq[i] > 0)
		{
			enqueue(pq, createTreeNode((char) i, freq[i], NULL,NULL), freq[i]);
		}
	}

	while (pq->head != NULL && pq->head->next != NULL)
	{
		TreeNode* left = dequeue(pq);
		TreeNode* right = dequeue(pq);
		int sum = left->freq + right->freq;
		enqueue(pq, createTreeNode('\0', sum, left, right), sum);
	}

	TreeNode* root = dequeue(pq);

	free(pq);
	return root;
}
