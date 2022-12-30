#include "pqueue.h"

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

struct pqueue_node *pqueue_node_create(char item, uint32_t freq)
{
    struct pqueue_node *node = (struct pqueue_node *) malloc(sizeof(struct pqueue_node));
    if (!node) {
        fprintf(stderr, "Error allocating memory for pqueue_node");
        return NULL;
    }

    node->item = item;
    node->freq = freq;
    node->left = node->right = NULL;

    return node;
}

struct pqueue *pqueue_create(uint32_t capacity)
{
    struct pqueue *queue = (struct pqueue *) malloc(sizeof(struct pqueue));
    if (!queue) {
        fprintf(stderr, "Error allocating memory for pqueue");
        return NULL;
    }

    queue->array = (struct pqueue_node **) malloc(sizeof(struct pqueue_node *) * capacity);
    if (!queue->array) {
        fprintf(stderr, "Error allocating memory for pqueue node array");
        return NULL;
    }

    queue->size = 0;
    queue->capacity = capacity;

    return queue;
}

void pqueue_node_free(struct pqueue_node *node)
{
    if (!node)
        return;
    
    pqueue_node_free(node->left);
    pqueue_node_free(node->right);
    free(node);
}

void pqueue_free(struct pqueue *queue)
{
    for (size_t i = 0; i < queue->size; ++i) {
        pqueue_node_free(queue->array[i]);
    }
    free(queue->array);
    free(queue);
}

void pqueue_swap(struct pqueue_node **a, struct pqueue_node **b)
{
    struct pqueue_node *temp = *a;
    *a = *b;
    *b = temp;
}

size_t pqueue_left(size_t index)
{
    return 2 * index + 1;
}

size_t pqueue_right(size_t index)
{
    return 2 * index + 2;
}

size_t pqueue_parent(size_t index)
{
    return (index - 1) / 2;
}

void pqueue_heapify(struct pqueue *queue, size_t index)
{
    assert(queue);
    assert(queue->array);

    size_t left = pqueue_left(index);
    size_t right = pqueue_right(index);
    size_t smallest = index;

    if (left < queue->size && queue->array[left]->freq < queue->array[smallest]->freq) {
        smallest = left;
    }

    if (right < queue->size && queue->array[right]->freq < queue->array[smallest]->freq) {
        smallest = right;
    }

    if (smallest != index) {
        pqueue_swap(&queue->array[smallest], &queue->array[index]);
        pqueue_heapify(queue, smallest);
    }
}

struct pqueue_node *pqueue_pop(struct pqueue *queue)
{
    if (queue->size == 0) {
        fprintf(stderr, "Error: pqueue is empty");
        return NULL;
    }
    
    struct pqueue_node *node = queue->array[0];
    queue->array[0] = queue->array[queue->size - 1];

    --queue->size;
    pqueue_heapify(queue, 0);

    return node;
}

int pqueue_push(struct pqueue *queue, struct pqueue_node *node)
{
    if (queue->size == queue->capacity) {
        fprintf(stderr, "Error: pqueue is full");
        return -1;
    }

    size_t i = queue->size;
    while (i && node->freq < queue->array[pqueue_parent(i)]->freq) {
        queue->array[i] = queue->array[pqueue_parent(i)];
        i = pqueue_parent(i);
    }

    queue->array[i] = node;
    ++queue->size;

    return 1;
}
