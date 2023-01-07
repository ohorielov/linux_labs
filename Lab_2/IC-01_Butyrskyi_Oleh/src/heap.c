#include"heap.h"
#include <stdlib.h>

#define heap_size 500


static void swap(Hnode **hNodes, int i, int j) {
	Hnode *temp = hNodes[i];
	hNodes[i] = hNodes[j];
	hNodes[j] = temp;
}

void initializeHeap(heap *h) {
	h->size = heap_size;
	h->top = -1;
	h->hNodes = (Hnode **) malloc(sizeof(Hnode*) * heap_size);
}

void heapPush(heap *heap_, Hnode *hNode) {
	heap_->hNodes[++heap_->top] = hNode;

	int index = (heap_->top);
	int parent = (index - 1) / 2;

	while (parent >= 0 && heap_->hNodes[index]->entries < heap_->hNodes[parent]->entries){
		swap(heap_->hNodes, index, parent);
		index = parent;
		parent = (parent - 1) / 2;
	}
}

Hnode* heapHead(heap heap) {
	return heap.hNodes[0];
}

void heapPop(heap *h) {
	if (h->top == -1) {
		return;
	}

	swap(h->hNodes, 0, h->top);

	h->top--;

	int index = 0;
	int left = 0; 
	int right = 0;
	while (index <= h->top) {
		left = (2 * index) + 1;
		right = (2 * index) + 2;

		if (left > h->top) {
			return;
		}

		if (right <= h->top) {
			int child = (h->hNodes[left]->entries < h->hNodes[right]->entries) ? left : right;

			if (h->hNodes[index]->entries > h->hNodes[child]->entries) {
				swap(h->hNodes, index, child);
				index = child;
			}
			else {
				break;
			}
		} else {
			int child = left;
			if (h->hNodes[index]->entries > h->hNodes[child]->entries) {
				swap(h->hNodes, index, child);
				index = child;
			} else  {
				break;
			}
		}
	}
}

int heapSize(heap h) {
	return h.top + 1;
}

void heapDestroy(heap *h) {
	free(h->hNodes);
}
