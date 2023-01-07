
#ifndef C_HUFF
#define C_HUFF

#include "huffman.h"
#include "heap.h"
#include <stdlib.h>
#include <limits.h>

Hnode* newHnode(char ch, int entries) {
	Hnode *nn = (Hnode*) malloc(sizeof(Hnode));
	nn->entries = entries;
	nn->symbol = ch;
	nn->left = nn->right = NULL;
	return nn;
}

void code(Hnode *root, unsigned long long *currentCodeWords, int *bit, HuffEncoder *e) {
	if (!root) {
		return;
	}

	if (root->left || root->right) {
		(*bit)++;
		code(root->left, currentCodeWords, bit, e);

		(*bit)--;
		*currentCodeWords = (*currentCodeWords) | (1ll << (*bit));
		
		(*bit)++;
		code(root->right, currentCodeWords, bit, e);

		(*bit)--;
		*currentCodeWords = (*currentCodeWords) ^ (1ll << (*bit));
	} else {
		e->codeWords[root->symbol] = *currentCodeWords;
		e->lengths[root->symbol] = *bit;
	}
}

void canonicalCode(HuffEncoder *e, Hnode *root) {
	for (int i = 0; i < huffman_symbols_limit; i++) {
		e->codeWords[i] = 0ll;
		e->lengths[i] = 0ll;
	}

	unsigned long long curr_codewords = 0ll;
	int bit = 0;
	code(root, &curr_codewords, &bit, e);
}

Hnode* deleteTree(Hnode *root) {
	if (!root) return NULL;
	root->left = deleteTree(root->left);
	root->right = deleteTree(root->right);
	Hnode *del = root;
	free(del);
	return NULL;
}

void createTree(HuffEncoder *e, int entries[], int n) {
	long long freq_sum = 0;
	for (int i = 0; i < n; i++) {
		freq_sum += entries[i];
	}

	heap h;
	initializeHeap(&h);
	for (int i = 0; i < n; i++) {
		if (entries[i]) {
			Hnode *nn = newHnode((char) i, entries[i]);
			heapPush(&h, nn);
		}
	}

	if (heapSize(h) == 1) {
		Hnode *front = heapHead(h);
		e->codeWords[front->symbol] = 0;
		e->lengths[front->symbol] = 1;
		heapDestroy(&h);
		return;
	}

	Hnode *root = NULL;
	while (heapSize(h) > 1) {
		Hnode *front1 = heapHead(h);
		heapPop(&h);
		Hnode *front2 = heapHead(h);
		heapPop(&h);

		Hnode *newNode = newHnode('-', front1->entries + front2->entries);
		heapPush(&h, newNode);

		newNode->left = front1;
		newNode->right = front2;
	}

	root = heapHead(h);
	canonicalCode(e, root);
	root = deleteTree(root);
	heapDestroy(&h);
}

void encoderInitialize(HuffEncoder *e, int entries[], int n) {
	for (int i = 0; i < huffman_symbols_limit; i++) {
		e->codeWords[i] = 0ll;
		e->lengths[i] = 0ll;
	}

	createTree(e, entries, n);
}

#endif
