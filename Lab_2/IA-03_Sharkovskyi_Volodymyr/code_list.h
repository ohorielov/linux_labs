typedef struct code {
   char symbol;
   struct code *next;
} code;

void codePrint(code *code_head);
int codeLength(code *head);
code* insertLast(char symbol, code *code_head);
code* deleteLast(code *code_head);
