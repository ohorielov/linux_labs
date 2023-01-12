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

typedef struct symbol_and_code{
    char symbol;
    code *code;
} symbol_and_code;

code* search_in_list(symbol_and_code symbol_code[], int n, char ch){
    code* searched_code;
    for (int i = 0; i < n; i++){
        searched_code = symbol_code[i].code;
        if (symbol_code[i].symbol == ch){
            break;
        }
    }
    
    return searched_code;
}

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

    *code_head = insertLast(tree->branch, *code_head);
  
    if (tree->symbol == ch) {
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
    
    deleteLast(*code_head);
    
    return false;
}

int main(void){ 

    // struct node *current = NULL;

    FILE *non_comp_file = fopen("../non_compressed_text.txt", "r");
    FILE *comp_file = fopen("../compressed_text.txt", "wb");

    char ch;
    short symbols_counter;
    unsigned Freq[256];
    int bits = 0;

    int *coded_text;
    
    char *non_comp_text;

    while((fgetc(non_comp_file)) != EOF){
        symbols_counter += 1;
    }

    printf("\n%u\n", symbols_counter);

    rewind(non_comp_file);
    
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
            //printf("Символ %c : %5u раз\n", i, Freq[i]);
            n++;
        }
    }

    for(int i = 0; i < n; i++){
        printf("Символ %c : %5u разів\n", symbols_list[i].symbol, symbols_list[i].count);
    }

    printf("\n");

    qsort(symbols_list, n, sizeof(SAC), cmpfunc);

    for(int i = 0; i < n; i++){
        printf("Символ %c : %5u разів\n", symbols_list[i].symbol, symbols_list[i].count);
    }

    node *head = NULL;
    for(int i = 0; i < n; i++){
        head = insertFirst(symbols_list[i].symbol, symbols_list[i].count, head);
    }




    while(head->next){
        node *left = head;
        node *right = head->next;

        tree_node *tree = malloc(sizeof(tree_node));


        tree->left = left->tree_node;
        tree->right = right->tree_node;
        tree->symbol = NULL;


        tree->left->branch = 0;
        tree->right->branch = 1;

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

    symbol_and_code symbol_code[n];

    for (int i = 0; i < n; i++){
        code *code_head = NULL;
        hasCode(head->tree_node, &code_head, symbols_list[i].symbol);

        symbol_code[i].symbol = symbols_list[i].symbol;
        symbol_code[i].code = code_head->next;

        printf("symbol: %c, code: ", symbol_code[i].symbol);
        codePrint(symbol_code[i].code);
    }

    // for (int i; i < n; i++){
    //     printf("symbol: %c code: ", symbol_code[i].symbol);
    //     codePrint(symbol_code[i].code);
    // }

    rewind(non_comp_file);

    

    for (int i = 0; i < symbols_counter; i++){

        char symbol = fgetc(non_comp_file);

        code* code_new = search_in_list(symbol_code, n, symbol);

        int j = 0;
        for(code *current = code_new; current != NULL; current = current->next) {
            int s = current->symbol;
            // fputc(current->symbol, comp_file);
            printf("%u", current->symbol);
            
            // code_string[j] = current->symbol;
            j++;
        }

        bits += codeLength(code_new);

        //fputs(code_string, comp_file);
        //fputc(' ', comp_file);

        // codePrint(code_new);

        // printf("%c", symbol);
    }

    rewind(non_comp_file);

    printf("\n%u\n", bits);
    printf("\n%u\n", bits / 8 + 1);

    coded_text = (int *)malloc(bits / 8 + 1);

    bits = 0;

    for (int i = 0; i < symbols_counter; i++){

        char symbol = fgetc(non_comp_file);

        code* code_new = search_in_list(symbol_code, n, symbol);

        code* code_without_minus = code_new->next;
        code_new = code_without_minus;

        int j = 0;
        for(code *current = code_new; current != NULL; current = current->next) {
            *(coded_text + bits) = current->symbol;
            bits++;
            //fputc(current->symbol, comp_file);
            
            // code_string[j] = current->symbol;
            j++;
        }

    //     //fputs(code_string, comp_file);
    //     //fputc(' ', comp_file);

    //     // codePrint(code_new);
    }    

    write(&coded_text, 676, 1, comp_file);

    
    fclose(comp_file);

    fclose(non_comp_file);

    return 0;
}

