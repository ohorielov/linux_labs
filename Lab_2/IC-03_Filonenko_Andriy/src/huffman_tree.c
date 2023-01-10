#include <stdio.h>
#include <stdlib.h>
#include "huffman_tree.h"

int node_is_leaf(TreeNode *node) {
    return node->left == NULL && node->right == NULL;
}

void delete_tree(TreeNode *root) {
    if(root == NULL) return;

    delete_tree(root->left);
    delete_tree(root->right);
    
    free(root);
}
