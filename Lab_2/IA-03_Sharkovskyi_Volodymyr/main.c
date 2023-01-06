#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "list.c"
#include "code_list.c"

typedef struct symbol_and_count {
    char symbol;
    int count;
} SAC;

int cmpfunc(const void * a, const void * b){

    SAC * str_a = (SAC *) a;
    SAC * str_b = (SAC *) b;
    if((*str_a).count == (*str_b).count){
        return strcmp(&(*str_b).symbol, &(*str_a).symbol);
    } else {
        return (*str_b).count - (*str_a).count;
    }
}

int hasCode(tree_node *tree, code **code_head, char ch) {

    if (!tree) return false;

    printf("branch: %c, symbol tree: %c\n", tree->branch, tree->symbol);

    *code_head = insertLast(tree->branch, *code_head);
    
    if (tree->symbol == ch) {
        printf("found, quiting\n");
        return true;
    }
    if(tree->left){
        if (hasCode(tree->left, code_head, ch)) {
            return true;
        } 
    }
    if (tree->right) {
        if (hasCode(tree->right, code_head, ch)) {
            return true;
        }
    }
    
    codePrint(*code_head);
    deleteLast(*code_head);
    
    return false;
}

int main(void){ 

    // struct node *current = NULL;

    FILE *non_comp_file = fopen("../non_compressed_text.txt", "r");

    char ch;
    short symbols_counter;
    unsigned Freq[256];
    
    char *non_comp_text;

    while((fgetc(non_comp_file)) != EOF){
        symbols_counter += 1;
    }

    // printf("\n%i\n", symbols_counter);

    fclose(non_comp_file);

    non_comp_file = fopen("../non_compressed_text.txt", "r");

    non_comp_text = malloc(symbols_counter * sizeof(char));

    for(int i = 0; i < symbols_counter; i++){
        ch = fgetc(non_comp_file);
        *(non_comp_text + i) = ch;
    }

    for(int i = 0; i < symbols_counter; i++){
        printf("%c", *(non_comp_text + i));
    }

    fclose(non_comp_file);

    non_comp_file = fopen("../non_compressed_text.txt", "r");
    
      /* Обнуление таблицы частот */
    memset(Freq, 0, 256 * sizeof(unsigned));
    
    /* Заполнение таблицы частот */
    while (!feof(non_comp_file)){
        Freq[fgetc(non_comp_file)] ++;
    }

    /* Вывод результата */

    int n = 0;
    for (int i = 0; i < 256; i++){
        if (Freq[i]){
            // printf("Символ %c : %5u раз\n", i, Freq[i]);
            n++;
        }
    }

    SAC symbols_list[n];

    n = 0;
    for (int i = 0; i < 256; i ++){
        if (Freq[i]){
            SAC sac;
            sac.count = Freq[i];
            sac.symbol = (char)i;
            symbols_list[n] = sac;
            // printf("Символ %c : %5u раз\n", i, Freq[i]);
            n++;
        }
    }    

    qsort(symbols_list, n, sizeof(SAC), cmpfunc);

    for(int i = 0; i < n; i++){
        printf("Символ %c : %5u разів\n", symbols_list[i].symbol, symbols_list[i].count);
    }

    fclose(non_comp_file);

    node *head = NULL;
    for(int i = 0; i < n; i++){
        head = insertFirst(symbols_list[i].symbol, symbols_list[i].count, head);
    }

    while(head->next){
        node *left = head;
        node *right = head->next;

        tree_node *tree = (tree_node *)malloc(sizeof(tree_node));

        tree->left = left->tree_node;
        tree->right = right->tree_node;
        tree->symbol = '0';

        tree->left->branch = '0';
        tree->right->branch = '1';

        int count = left->count + right->count;

        head = deleteFirst(head);
        head = deleteFirst(head);
        if(head){
            head = insertNodeByPriority(tree, count, head);
        } else{
            head = (node *)malloc(sizeof(node));
            head->tree_node = tree;
            head->count = count;
            head->tree_node->branch = '-';
        } 
    }

    printf("\n");
    printList(head);
    printf("\n");

    tree_node *tree = head->tree_node;

    code *code_head = NULL;
    hasCode(tree, &code_head, 'e');

    codePrint(code_head);

    return 0;
}
