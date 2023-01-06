#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "tree.c"

typedef struct node {
   tree_node *tree_node;
   int count;

   struct node *next;
} node;

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

//insert link at the first location
struct node* insertFirst(char symbol, int count, node *head) {
   //create a link
   tree_node *tree = (tree_node *)malloc(sizeof(tree_node));
   node *link = (node*)malloc(sizeof(node));

	tree->symbol = symbol;
   tree->left = NULL;
   tree->right = NULL;
   tree->branch = '-';
   link->tree_node = tree;
   link->count = count;
	
   //point it to old first node
   link->next = head;
	
   //point first to new first node
   head = link;

   return head;
}

node* insertNodeByPriority(tree_node *tree, int count, node *head) {

   node *new_node = (node *)malloc(sizeof(node));

   new_node->tree_node = tree;
   new_node->count = count;
	
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

   return link;
}

//find a link with given key
node* find(char symbol, node *head) {

   //start from the first link
   node* current = head;

   //if list is empty
   if(head == NULL) {
      return NULL;
   }

   //navigate through list
   while(current->tree_node->symbol != symbol) {
	
      //if it is last node
      if(current->next == NULL) {
         return NULL;
      } else {
         //go to next link
         current = current->next;
      }
   }      
	
   //if count found, return the current Link
   return current;
}