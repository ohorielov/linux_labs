#ifndef PQUEUE_H
#define PQUEUE_H

#include <stddef.h>
#include <stdint.h>

struct pqueue_node
{
    char item;
    uint32_t freq;
    struct pqueue_node *left, *right;
};

struct pqueue
{
    size_t size;
    size_t capacity;
    struct pqueue_node **array;
};

#define PQUEUE_NODE_IS_LEAF(node) (((node)->left == NULL) && ((node)->right == NULL))

struct pqueue_node *pqueue_node_create(char item, uint32_t freq);

struct pqueue *pqueue_create(uint32_t capacity);

void pqueue_node_free(struct pqueue_node *node);

void pqueue_free(struct pqueue *queue);

void pqueue_swap(struct pqueue_node **a, struct pqueue_node **b);

size_t pqueue_left(size_t index);

size_t pqueue_right(size_t index);

size_t pqueue_parent(size_t index);

void pqueue_heapify(struct pqueue *queue, size_t index);

struct pqueue_node *pqueue_pop(struct pqueue *queue);

int pqueue_push(struct pqueue *queue, struct pqueue_node *node);

#endif // PQUEUE_H
