#ifndef TREE_H
#define TREE_H

#include "stdlib.h"
#include "stdbool.h"

struct Node;
struct ListNode;

typedef struct node {
    char character;
    int count;
    struct node *left;
    struct node *right;
} Node;
  
typedef struct listNode {
    struct node* data;
    struct listNode* next;
} ListNode;

struct CharCode;

typedef struct charCode {
    char character;
    char* coded;
    int size;
} CharCode;

void addCharacterToList(ListNode** head, char c, int* countChars);
void sortList (ListNode** head);
void createTree (ListNode** head);
void createCodes (CharCode* codes, int countcodes, Node* root, int code, int count); 
void insertToCharCodeList(CharCode* codes, int countCodes, char c, char* str, int count);
char* convert(int code, int count);
char* getCode(CharCode* codes, int countCodes, char c, int* size);
bool getCharacter(CharCode* codes, int countCodes, char* code, char* result);

#endif