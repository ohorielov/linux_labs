#include "tree.h"
#include "stdio.h"
#include "string.h"

void addCharacterToList(ListNode** head, char c, int* countChars) { 
    ListNode* current = *head;
    ListNode* previousNode = current;
    while (current) {
        if (current->data->character == c) {
            current->data->count++;
            break;
        } else {
            previousNode = current;
            current = current->next;
        }
    }
    if (current == NULL) {
        ListNode* tempNode;
        (*countChars)++;
        tempNode = malloc(sizeof(ListNode));
        tempNode->data = malloc(sizeof(Node));
        tempNode->data->character = c;
        tempNode->next = NULL;
        tempNode->data->left = NULL;
        tempNode->data->right = NULL;
        tempNode->data->count = 1;
        if (previousNode == NULL) {
            *head = tempNode;
        } else {
            previousNode->next = tempNode; 
        }
    }
}

void sortList(ListNode** head) {
    ListNode* current = *head;
    while (current) {
        ListNode* currNext = current->next;
        if (currNext) {
            if (currNext->data->count < current->data->count) {
                if (currNext->data->count <= (*head)->data->count) {
                    current->next = current->next->next;
                    currNext->next = *head;
                    *head = currNext;
                }
                else {
                    ListNode* temp = *head;
                    while (currNext->data->count > temp->next->data->count) {
                        temp = temp->next;
                    }   
                    current->next = current->next->next;
                    currNext->next = temp->next;
                    temp->next = currNext;
                }         
            }
            else {
                current = current->next;
            }
        }
        else {
            current = NULL;
        }
    }
}

void createTree(ListNode** head) {
    ListNode* current = *head;
    while (current->next) {
        Node* tempNode;
        tempNode = malloc(sizeof(Node));
        tempNode->character = 0;
        tempNode->count = current->data->count + current->next->data->count;
        tempNode->left = current->data;
        tempNode->right = current->next->data;
        ListNode* tempNodeList = current->next;
        while (tempNodeList->next != NULL  &&  tempNodeList->next->data->count < tempNode->count) {
            tempNodeList = tempNodeList->next;
        }
        if (current->next == tempNodeList) {
            ListNode* temp = current;
            current = current->next;  
            current->data = tempNode;         
            free(temp);
        } else {
            ListNode* temp = current;
            ListNode* nexttemp = current->next;
            current = nexttemp->next;
            nexttemp->next = tempNodeList->next;
            tempNodeList->next = nexttemp;
            nexttemp->data = tempNode;
            free(temp);
        }

    }
    *head = current;
}

char* convert(int code, int count) {
    char* str = malloc((size_t)count+1);
    str[count] = 0;
    for (int i=0; i<count; i++) {
        str[i] = (code & (int)1) + '0';
        code = code >> 1;
    }
    return str;
}

void insertToCharCodeList(CharCode* codes, int countCodes, char c, char* str, int count) {
    int i = 0;
    while (i < countCodes && codes[i].character != c) {
        i++;
    }
    if (codes[i].character == c) {
        codes[i].coded = str;
        codes[i].size = count;
    }
}


void createCodes (CharCode* codes, int countCodes, Node* root, int code, int count) {
    if (root) {
        createCodes(codes, countCodes, root->left, code & ~((int)0x1 << count), count + 1);
        createCodes(codes, countCodes, root->right, code | ((int)0x1 << count), count + 1);
        if (root->left == NULL  &&  root->right == NULL) {
            insertToCharCodeList(codes, countCodes, root->character, convert(code,count), count);
        }
    }
}

char* getCode(CharCode* codes, int countCodes, char c, int* size) {
    int i = 0;
    while (i < countCodes && codes[i].character != c) {
        i++;
    }
    if (codes[i].character == c) {
        *size = codes[i].size;
        return codes[i].coded;
    }
    return NULL;
}

bool getCharacter(CharCode* codes, int countCodes, char* code, char* result) {
    int i = 0;
    while (i < countCodes && strcmp(codes[i].coded, code) != 0) {
        i++;
    }
    if (i < countCodes && strcmp(codes[i].coded, code) == 0) {
        *result = codes[i].character;
        return true;
    }
    return false;
}
