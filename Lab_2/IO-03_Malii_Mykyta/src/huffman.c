#include "huffman.h"

int num_of_nodes = 0;
int queue_end = 1;
int bytes_after_encode = 0;

Node nodes[255], *queue = nodes - 1;             //the priority of a queue
struct Node_struct tree[256] = {{0}};        //tree of nodes
char *code[FREQUENCY_SIZE] = {0};                //a string array of the codes for each character
char buf[1024];

void read_file(FILE *fp_in, unsigned int *frequency) {
    char character, symbol[16] = {0};
    int i = 0;
    printf("File Read:\n");

    while ((character = fgetc(fp_in)) != EOF) {
        frequency[(int) character]++;                //read the file character by character and increment the frequency
        putchar(character);
    }

    for (i = 0; i < FREQUENCY_SIZE; i++)
        if (frequency[i])
            insert_into_queue(
                    create_node(frequency[i], i, 0, 0)
            );  //insert new nodes into the queue if there is a frequency


    while (queue_end > 2)
        insert_into_queue(
                create_node(0, 0, remove_in_queue(), remove_in_queue())
        );    //build the tree
    assign_code(queue[1], symbol, 0);        //assign the code for the characters
}

//Assign the code for each character
void assign_code(Node node, char *symbol, int len) {
    static char *out = buf;
    if (node->symbol) {
        symbol[len] = 0;        //if the provided node is a leaf (end node)
        strcpy(out, symbol);        //it contains a character
        code[(int) node->symbol] = out;    //therefore the code is copied in to the relevant character.
        out += len + 1;        //out pointer is incremented
        return;
    }

    symbol[len] = '0';
    assign_code(node->left, symbol, len + 1);    //recurring is used to write out the code
    symbol[len] = '1';
    assign_code(node->right, symbol, len + 1);    //if right add a 1 and if right add a 0
}

//function used to create a new node
Node create_node(int frequency, char symbol, Node x, Node y) {
    Node node = tree + num_of_nodes++;

    if (frequency != 0) {
        node->symbol = symbol;
        node->frequency = frequency;
    } else {
        node->left = x, node->right = y;                    //if there is no frequency provided with the invoking
        node->frequency = x->frequency +
                          y->frequency;        //the removed nodes at the end of the que will be added to left and right
    }
    return node;
}

//insert a node into the priority queue
void insert_into_queue(Node node) {
    int i, j = queue_end++;
    while ((i = j / 2)) {
        if (queue[i]->frequency <= node->frequency)
            break;
        queue[j] = queue[i];
        j = i;
    }
    queue[j] = node;
}

Node remove_in_queue() {
    int i, j;
    Node node = queue[i = 1];

    if (queue_end < 2)
        return 0;

    queue_end--;
    while ((j = i * 2) < queue_end) {
        if (j + 1 < queue_end && queue[j + 1]->frequency < queue[j]->frequency)
            j++;
        queue[i] = queue[j], i = j;
    }
    queue[i] = queue[queue_end];
    return node;
}

void print_table(unsigned int *frequency) {
    int i;
    printf("\n\nCodes table\n\n");
    for (i = 0; i < FREQUENCY_SIZE; i++) {
        if (isprint((char) i) && code[i] != NULL && i != ' ')
            printf("%-6c  %-6d  %s\n", i, frequency[i], code[i]);
        else if (code[i] != NULL) {
            switch (i) {
                case ' ':
                    printf("\' \' ");
                    break;
                case '\n':
                    printf("\\n  ");
                    break;

                case '\t':
                    printf("\\t  ");
                    break;
            }
            printf("    %-6d  %s\n", frequency[i], code[i]);
        }
    }
    printf("\n");
}


FILE *encoding(unsigned int *frequency, char filename[FILENAME_SIZE], FILE *fp_in, FILE *fp_out) {

    strcpy(filename, "compressed_text.txt");
    fp_out = fopen(filename, "w");

    char input_file, character, temp[20] = {0};
    int i, j = 0, k = 0, limit = 0;

    //point to start of file
    rewind(fp_in);

    for (i = 0; i < FREQUENCY_SIZE; i++) {
        if (frequency[i])
            limit += (frequency[i] * strlen(code[i]));
    }
    bytes_after_encode = limit;            //The output data is equal to the limit
    fprintf(fp_out, "%04d\n", limit);
    printf("\nEncoded:\n");
    for (i = 0; i < limit; i++) {
        if (temp[j] == '\0') {
            input_file = fgetc(fp_in);
            strcpy(temp, code[input_file]);
            printf("%s", code[input_file]);
            j = 0;
        }

        if (temp[j] == '1')
            character = character | (1 << (7 - k));       //shifts 1 to relevant position and OR with the temporary char
        else if (temp[j] == '0')
            character = character | (0 << (7 - k));       //shifts 0 to relevant position and OR with the temporary char
        else
            printf("Wrong input\n");
        k++;                            // k is used to divide the string into 8 bit chunks and save
        j++;
        if (((i + 1) % 8 == 0) || (i == limit - 1)) {
            k = 0;
            fputc(character, fp_out);
            character = 0;
        }

    }
    putchar('\n');

    return fp_out;
}

void decoding(FILE *fp_encode, FILE *fp_out, char filename[FILENAME_SIZE]) {
    int i = 0, j = 0, limit = 0;
    char character;
    Node node = queue[1];

    fscanf(fp_encode, "%d", &limit);                //get the length of the bitstream from header
    fseek(fp_encode, 1, SEEK_CUR);             //seek one position to avoid new line character of the header

    printf("\n");
    for (i = 0; i < limit; i++) {
        if (j == 0)
            character = fgetc(fp_encode);
        //if the ending of the character with b1000 0000 is true then,
        if (character & 128)
            node = node->right;
        else
            node = node->left;
        if (node->symbol) {                            //until node with a character meets
            putchar(node->symbol);                  //spit that character out and save the character in file
            fputc(node->symbol, fp_out);
            node = queue[1];                           //reset the que
        }
        character = character << 1;                    //shift the character by 1
        if (++j > 7)
            j = 0;
    }
    putchar('\n');

    remove(filename);
}


FILE *open_file(FILE *fp_in, char filename[FILENAME_SIZE], int argc, char *argv[]) {

    if (argc == 2) {
        strcpy(filename, argv[1]);
    } else {
        printf("Enter the file to encode: ");
        exit(0);
    }

    fp_in = fopen(filename, "r");
    if (fp_in == NULL) {    //open the file stream
        printf("\nno such file\n");
        exit(0);
    }

    return fp_in;
}

FILE *file_for_decode(FILE *fp_in, char filename[FILENAME_SIZE], char *mode) {
    fp_in = fopen(filename, mode);
    if (fp_in == NULL) {
        printf("\nno such file\n");
        exit(0);
    }
    return fp_in;
}


FILE *create_table(FILE *fp_out, char filename[FILENAME_SIZE], unsigned int *frequency) {

    strcat(filename, ".table");            //write the frequency table in .table extension

    fp_out = fopen(filename, "w");
    for (int i = 0; i < FREQUENCY_SIZE; i++) {
        fprintf(fp_out, "%c", (char) frequency[i]);                    //write the frequency to .table file
    }

    return fp_out;
}

void read_table(FILE *fp_table, unsigned int *frequency) {
    char character;                        //temporary variable
    int i = 0;

    while ((character = fgetc(fp_table)) != EOF) {
        frequency[i++] = (unsigned char) character;        //get the values from the .table file to update the huffman tree
    }
    for (i = 0; i < FREQUENCY_SIZE; i++)
        if (frequency[i])
            insert_into_queue(
                    create_node(frequency[i], i, 0, 0));    //insert new nodes into the que if there is a frequency
    while (queue_end > 2)
        insert_into_queue(create_node(0, 0, remove_in_queue(), remove_in_queue()));        //build the tree
}


void calculate_bytes(unsigned int *frequency) {
    int bytes_before_encode = 0;

    for (int i = 0; i < FREQUENCY_SIZE; i++) {
        bytes_before_encode += frequency[i];            //calculate bytes before encode
    }

    bytes_after_encode /= 8;

    if (bytes_after_encode % 8) {
        bytes_after_encode++;
    }
    printf("\nBefore encoding file weight - %d, after encoding - %d\n\n", bytes_before_encode, bytes_after_encode);

}

void calculate_bytes_after_decoding(unsigned int *frequency) {
    int bytes_after_decode = 0;

    for (int i = 0; i < FREQUENCY_SIZE; i++) {
        bytes_after_decode += frequency[i];            //calculate bytes before encode
    }

    printf("\nAfter decoding file bitstream = %d\n", bytes_after_decode);
}


void clear_data(char filename[FILENAME_SIZE], unsigned int *frequency) {
    strcpy(filename, "");

    memset(tree, 0, sizeof tree);
    memset(frequency, 0, FREQUENCY_SIZE);

    num_of_nodes = 0;
    queue_end = 1;
    queue = nodes - 1;             //the priority queue
}