#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

#define MAX_TREE_HT 50

int code[256][256]; // Array in which the binary code for the characters is stored
int alphabet_size_freq[256];
int bool_letter_dict[256];  // An array containing 0 and 1, which is responsible for whether there is a character with code [i] inside the alphabet
char* input_buf;  // Buffer with incoming text

struct node //vertex of the graph in which we store the letter, its frequency and the two pointers to leaves
{ 
    char item;  // the letter
    unsigned freq;  // the frequency
    struct node* left, * right;  // two pointers to leaves
};

struct tree //a structure for storing tree vertices
{ 
    unsigned size; // Current Tree size
    unsigned capacity; // The required capacity of the tree, which is equal to the size of the alphabet
    struct node** graph; // The tree itself
};

struct node* add_node(char item, unsigned freq) // Function to create a new node to be added to the tree
{
    struct node* new_node = (struct node*)malloc(sizeof(struct node));

    new_node->left = new_node->right = NULL;
    new_node->item = item;
    new_node->freq = freq;

    return new_node;
}

struct tree* create_tree(unsigned capacity) // function to initialise the tree
{ 
    struct tree* tree = (struct tree*)malloc(sizeof(struct tree));

    tree->size = 0; // Size 0, because the tree is initially empty and has no vertices
    tree->capacity = capacity; // Here you specify the required capacity, which is equal to the size of the alphabet
    tree->graph = (struct node**)malloc(tree->capacity * sizeof(struct node*));

    return tree;
}

void sort_tree(struct tree* tree, int subtree_root) // function for sorting the vertices of a tree in ascending order
{
    int smallest_node = subtree_root;
    int left_child = 2 * subtree_root + 1;
    int right_child = 2 * subtree_root + 2;

    if (left_child < tree->size && tree->graph[left_child]->freq < tree->graph[smallest_node]->freq)
        smallest_node = left_child;

    if (right_child < tree->size && tree->graph[right_child]->freq < tree->graph[smallest_node]->freq)
        smallest_node = right_child;

    if (smallest_node != subtree_root) // If the parent is the minimum, all is well, otherwise put the minimum in place 
    { 
                           // of the parent and keep going down deeper to sort the subtrees
        struct node* tmp = tree->graph[smallest_node];
        tree->graph[smallest_node] = tree->graph[subtree_root];
        tree->graph[subtree_root] = tmp;
        sort_tree(tree, smallest_node);
    }
}

struct node* extract_min_code(struct tree* tree) // the function takes the vertex with the minimum code, removes it from the tree and returns
{  
    struct node* temp = tree->graph[0]; // The minimum code will always be in the root of the tree
    tree->graph[0] = tree->graph[tree->size - 1];  // Remove the root, put the last element in its place 
                                                   // (because after downsizing the last vertex will be "deleted") and do a sorting
    tree->size -= 1;
    sort_tree(tree, 0);

    return temp;
}

void push_node(struct tree* tree, struct node* treeNode) // the function adds a vertex to the tree
{ 
    tree->size += 1;
    int i;
    for (i = tree->size - 1; i && treeNode->freq < tree->graph[(i - 1) / 2]->freq; i = (i - 1) / 2) // go through the tree from the end to find the best place for the new vertex
    {
        tree->graph[i] = tree->graph[(i - 1) / 2];
    }
    tree->graph[i] = treeNode; // adding a new vertex
}

void build_tree(struct tree* tree) 
{
    int n = tree->size - 1;
    int i;

    for (i = (n - 1) / 2; i >= 0; i--)  // Sort all the subtrees 
        sort_tree(tree, i);
}

void create_huffman_code(struct node* root, int arr[], int top) 
{
    if (root->left) 
    {
        arr[top] = 0;
        create_huffman_code(root->left, arr, top + 1);
    }
    if (root->right) 
    {
        arr[top] = 1;
        create_huffman_code(root->right, arr, top + 1);
    }
    if (!(root->left) && !(root->right)) 
    {
        int i;
        for (i = 0; i < top; i++)
        {
            code[root->item][i] = arr[i];
        }
        code[root->item][i] = -1; // "stop-symbol"
    }
}

void read_file(char *input_file_name)
{
    FILE* file;
    long size;

    file = fopen(input_file_name, "r");
    fseek(file, 0, SEEK_END); 
    size = ftell(file); 
    fseek(file, 0, SEEK_SET);

    input_buf = malloc(sizeof(char) * size);
    memset(input_buf, 0, size);

    fread(input_buf, sizeof(char), size, file);

    fclose(file);
}

void make_alphabet(int *size) {
    for (int i = 0; i < strlen(input_buf); i++)
    {
        if (bool_letter_dict[(int)(input_buf[i])] != 1 && ((input_buf[i] >= 32 && input_buf[i] <= 126) || input_buf[i] == 10)) 
        {
            bool_letter_dict[(int)(input_buf[i])] = 1;
            (*size)++;
        }
        alphabet_size_freq[input_buf[i]]++;
    }
}

void decode(char* input_file_name, char *output_file_name) 
{
    FILE* input_file;
    long size;

    input_file = fopen(input_file_name, "r");
    fseek(input_file, 0, SEEK_END);
    size = ftell(input_file);
    fseek(input_file, 0, SEEK_SET);

    input_buf = malloc(sizeof(char) * size);
    memset(input_buf, 0, size);
    fread(input_buf, sizeof(char), size, input_file);
    fclose(input_file);
    FILE* output_file = fopen(output_file_name, "w");

    for (int i = 0; i < strlen(input_buf); i++) 
    {
        for (int j = 1; j < strlen(input_buf) - i; j++) 
        {
            int checked = 1;
            for (int m = 0; m < 256 && checked == 1; m++) 
            {
                if (bool_letter_dict[m] != 1 || code[m][j] != -1)
                    continue;
                checked = 0;
                for (int g = i; g < i + j; g++) 
                {
                    if (code[m][g - i] != input_buf[g] - '0')
                    {
                        checked = 1;
                        break;
                    }
                }
                if (checked == 0)
                    fprintf(output_file, "%c", (char)(m));
            }
            if (checked == 0) 
            {
                i += j - 1;
                break;
            }
        }
    }
}
int main() 
{
    read_file("non_compressed_text.txt");

    int size = 0;

    make_alphabet(&size);

    char* arr = (char*)malloc(size * sizeof(int));
    int *freq = (int*)malloc(size * sizeof(int));

    memset(arr, 0, size * sizeof(char));
    memset(freq, 0, size * sizeof(char));

    int indx = 0;

    for (int i = 0; i < 127; i++)
    {
        if (bool_letter_dict[i] == 1) 
        {
            arr[indx] = (char)(i);
            freq[indx] = alphabet_size_freq[i];
            indx++;
        }
    }

    struct node* left, * right, * top;
    struct tree* tree = create_tree(size);

    for (int i = 0; i < size; ++i)
        tree->graph[i] = add_node(arr[i], freq[i]);

    tree->size = size;
    build_tree(tree);

    for (int i = 0; i < size - 1; i++) 
    {
        left = extract_min_code(tree);
        right = extract_min_code(tree);

        top = add_node(NULL, left->freq + right->freq);

        top->left = left;
        top->right = right;

        push_node(tree, top);
    }
    struct node* root = extract_min_code(tree);

    int code_tmp_arr[MAX_TREE_HT], top_indx = 0;

    create_huffman_code(root, code_tmp_arr, top_indx);


    FILE *output_file = fopen("compressed_text.txt", "w");

    for (int i = 0; i < strlen(input_buf); i++)
    {
        if ((input_buf[i] < 32 || input_buf[i] > 126) && input_buf[i] != 10)
            continue;

        for (int j = 0; code[input_buf[i]][j] != -1; j++) 
        {
            fprintf(output_file, "%d", code[input_buf[i]][j]);
        }
    }

    fclose(output_file);

    decode("compressed_text.txt", "new_non_compressed_text.txt");
}