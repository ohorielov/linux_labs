typedef struct tree_node {
    char symbol;
    char branch;
    struct tree_node *left, *right;
} tree_node;

typedef struct node {
   tree_node *tree_node;
   int count;

   struct node *next;
} node;

void printList(node *head);
node* insertFirst(char symbol, int count, node *head);
node* insertNodeByPriority(tree_node *tree, int count, node *head);
node* deleteFirst(node *head);
node* find(char symbol, node *head);
