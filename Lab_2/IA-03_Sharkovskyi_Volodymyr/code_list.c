#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct code {
   int symbol;

   struct code *next;
} code;

void codePrint(code *code_head){
    code *link = code_head;

    while(link){
        printf("%u", link->symbol);
        link = link->next;
    }
    printf("\n");
}

int codeLength(code *head) {
   int length = 0;
   code *current;
	
   for(current = head; current != NULL; current = current->next) length++;
	
   return length;
}

code* insertLast(int symbol, code *code_head) {
    code *new_code = (code *)malloc(sizeof(code));
    new_code->symbol = symbol;
    
    if (code_head == NULL) {
        code_head = new_code;
        return code_head;
    }

    code *link = code_head;

    while (link->next) link = link->next;

    link->next = new_code;
    link->next->next = NULL;

    return code_head;
}

code* deleteLast(code *code_head){
    code *link = code_head;
    if (!link) return NULL;
    if (link->next) {
        while (link->next->next) link = link->next;
        free(link->next);
        link->next = NULL;
    } else {
        free(code_head);
        code_head = NULL;
    }

    return code_head;
}
