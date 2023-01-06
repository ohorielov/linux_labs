#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct tree_node {
    char symbol;
    char branch;

    struct tree_node *left, *right;
} tree_node;
