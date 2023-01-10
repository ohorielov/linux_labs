typedef struct TreeNode {
    int value;
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode;

int node_is_leaf(TreeNode *node);
void delete_tree(TreeNode *root);
