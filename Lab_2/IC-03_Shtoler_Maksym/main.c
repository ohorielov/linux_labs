#include "stdlib.h"
#include "stdio.h"
#include "tree.h"
#include "string.h"

void printText(char* text, int textSize);

int main() {
    ListNode* head = NULL;
    CharCode* codes;

    const char* inputName = "../non_compressed_text.txt";
    const char* outputName = "../compressed_text.txt";

    FILE* input = fopen(inputName, "r");
    FILE* output = fopen(outputName, "w");

    char text;
    int countChars = 0;
    int fileSize = 0;
    while(fread(&text, sizeof(char), 1, input)) {
        addCharacterToList(&head, text, &countChars);
        fileSize++;
    }

    // Allocate memory for final codes list
    codes = malloc(sizeof(CharCode)*countChars);

    // Init chars in codes list
    ListNode* tempNode = head;
    int i = 0;
    while (tempNode) {
        codes[i].character = tempNode->data->character;
        i++;
        tempNode = tempNode->next;
    }

    sortList(&head);
    createTree(&head);
    createCodes(codes, countChars, head->data, 0, 0);

    // Print codes
    for (i = 0; i < countChars; i++) {
       printf("%c = %s\n",codes[i].character,codes[i].coded);
    }
    printf("\n");

    // Create coded txt file
    rewind(input);
    i = 0;
    char* inputStr = malloc(fileSize);
    while(fread(&text, sizeof(char), 1, input)) {
        inputStr[i++] = text;
        char* str;
        int size;
        str = getCode(codes, countChars, text, &size);
        if (str) {
            fwrite(str, size, 1, output);
        }
    }

    // Decode string from coded txt file
    fclose(output);
    output = fopen(outputName, "r"); 
    char readText[32];
    char* decodedText = malloc(fileSize);
    int index = 0;
    i = 0;
    while(fread(&text, sizeof(char), 1, output)) {
        readText[index] = text;
        readText[index + 1] = 0;
        char readCharacter;
        bool success = getCharacter(codes, countChars, readText, &readCharacter);
        if (success) {
            decodedText[i++] = readCharacter;
            index = 0;
        } else {
            index++;
        }
    }

    printf("Input text: ");
    printText(inputStr, fileSize);
    printf("\n");

    printf("Decoded text: ");
    printText(decodedText, fileSize);
    printf("\n");

    // Compare input and decoded files
    int result = memcmp(inputStr, decodedText, fileSize);
    if (result == 0) {
        printf("Decoded text is equal to input\n\n");
    } else {
        printf("ERROR: Decoded text is NOT equal to input\n\n");
    }
}

void printText(char* text, int textSize) {
    for (int i = 0; i < textSize; i++) {
        printf("%c", text[i]);
    }
}