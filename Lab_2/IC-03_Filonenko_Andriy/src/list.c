#include <stdio.h>
#include <stdlib.h>
#include "huffman_tree.h"
#include "list.h"
#define CHARACTER_LIMIT 256

ListNode *init_sorted_list(int *char_frequency) {
    ListNode *head = NULL;

    for (int i = 0; i < CHARACTER_LIMIT; i++) {
        if (char_frequency[i] == 0) continue;

        ListNode *list_node = malloc(sizeof(ListNode));

        if (list_node == NULL) return NULL;

        list_node->char_frequency = char_frequency[i];      
        list_node->parent = malloc(sizeof(TreeNode)); 
        list_node->parent->left = NULL; 
        list_node->parent->right = NULL;
        list_node->parent->value = i;   
        list_node->next = NULL; 

        head = add_element_sorted(head, list_node);
    }
    
    if(head == NULL) return NULL;

    return head;
}


int determine_size(ListNode *to_add, ListNode *cur) {
    if (to_add->char_frequency < cur->char_frequency) {
        return 1;
    } else if (to_add->char_frequency == cur->char_frequency) {
        if (node_is_leaf(to_add->parent) && !node_is_leaf(cur->parent))  {
            return 1;
        }
        else if (node_is_leaf(to_add->parent) && node_is_leaf(cur->parent)) {
            if (to_add->parent->value < cur->parent->value)
                return 1;
            return 0;
        }
        return 0;
    }
    return 0;
}

ListNode *add_element_sorted(ListNode *head_node, ListNode *list_node) {
    if (head_node == NULL || head_node == list_node) return list_node;

    ListNode *current_node = head_node;
    ListNode buffer_node;
    buffer_node.next = head_node;
    ListNode *previous_node = &buffer_node;

    while (current_node != NULL) {
        if (determine_size(list_node, current_node)) {
            list_node->next = current_node;
            previous_node->next = list_node;
            head_node = buffer_node.next;  
            return head_node;
        }  else {
            previous_node = current_node;
            current_node = current_node->next;
        }
    }
    previous_node->next = list_node;

    return head_node;
}
