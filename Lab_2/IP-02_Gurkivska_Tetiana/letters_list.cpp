#include <iostream>
#include <string>
#include "letters_list.h"
using namespace std;

void letters_list::add_node(char c) {
    node* temp = head;
    node* last_temp = head;
    while (temp) {
        if (temp->ch == c) {
            temp->amount++;
            break;
        }
        else {
            last_temp = temp;
            temp = temp->next;
        }
    }
    if (temp == NULL) {
        node* tempNode = new node();
        letters_amount++;
        tempNode->ch = c;
        tempNode->next = NULL;
        tempNode->amount = 1;
        if (last_temp == NULL) {
            head = tempNode;
        }
        else {
            last_temp->next = tempNode;
        }
    }
}

void letters_list::print_list() {
    node* temp = head;
    while (temp) {
        cout<<temp->ch<<" - "<< temp->amount<< endl;
        temp=temp->next;
    }
}

void letters_list::sort_list() {
    for (int i = 0; i < letters_amount - 1; i++) {
        for (int j = 0; j < letters_amount - 1; j++) {
            node* node_0 = head;
            node* node_1 = head;
            node* node_2 = head;
            node* node_3 = head;
            if (j != 0) {
                for (int k = 0; k < j - 1; k++) {
                    node_0 = node_0->next;
                }
                node_1 = node_0->next;
            }
            node_2 = node_1->next;
            node_3 = node_2->next;
            if (node_2->amount < node_1->amount) {           
                if (j != 0) {
                    node_0->next = node_2;
                }
                node_2->next = node_1;
                node_1->next = node_3;
                if (j == 0) {
                    head = node_2;
                }

            }
            
        }
    }
}

node* letters_list::transform(node* head) {
    node* temp = head;
    while (temp->next) {
        node* tempNode = new node();
        tempNode->ch = '0';
        tempNode->amount = temp->amount + temp->next->amount;
        tempNode->left = temp;
        tempNode->right = temp->next;
        node* tempList = temp->next;
        while (tempList->next != NULL && tempList->next->amount < tempList->amount) {
            tempList = tempList->next;
        }
        if (temp->next == tempList) {
            temp = temp->next;
            node* cur = temp->next;
            temp = tempNode;
            temp->next = cur;

        }
        else {
            node* nextcur = temp->next;
            temp = nextcur->next;
            nextcur->next = tempList->next;
            tempList->next = nextcur;

            nextcur->amount = tempNode->amount;
            nextcur->ch = tempNode->ch;
            nextcur->left = tempNode->left;
            nextcur->right = tempNode->right;
            free(nextcur);
        }

    }
    return temp;

}