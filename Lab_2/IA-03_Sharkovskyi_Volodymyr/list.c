#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#include "list.h"

void printList(node *head) {
   node *ptr = head;
   printf("\n[");
	
   //start from the beginning
   while(ptr != NULL) {
      printf("(%c,%d)", ptr->tree_node->symbol, ptr->count);
      ptr = ptr->next;
   }
   printf("]");
}

node* insertFirst(char symbol, int count, node *head) {

   tree_node *tree = (tree_node *)calloc(sizeof(tree_node), 1);
   node *link = (node*)calloc(sizeof(node), 1);

	tree->symbol = symbol;
   tree->left = NULL;
   tree->right = NULL;
   tree->branch = '-';
   link->tree_node = tree;
   link->count = count;
   link->next = NULL;
	
   if (head != NULL){
      link->next = head;
      head = link;
   } else {
      head = link;
   }

   return head;
}

node* insertNodeByPriority(tree_node *tree, int count, node *head) {

   node *new_node = (node *)calloc(sizeof(node), 1);

   new_node->tree_node = tree;
   new_node->count = count;

   new_node->next = NULL;
	
   node *link = head;
   
   while (link->next && new_node->count > link->next->count){
      link = link->next;
   }

   node *link_next = link->next;
   new_node->next = link_next;
   link->next = new_node;

   return head;
}

node* deleteFirst(node *head) {

   if (!head){
      return head;
   }
   
   node *link = head->next;

   free(head);

   head = link;

   return head;
}
