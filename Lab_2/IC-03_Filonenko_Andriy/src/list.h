typedef struct ListNode {
    TreeNode *parent;
    struct ListNode *next;
    int char_frequency;
} ListNode;

ListNode *init_sorted_list(int *);
ListNode *add_element_sorted(ListNode *, ListNode *);
int determine_size(ListNode *, ListNode *);
