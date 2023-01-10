void build_table_(TreeNode *, char *, char, char **, int, int *);
void write_huffman_binary_structure(TreeNode *, FILE *, int *, int *, long *);
void write_encoded_characters(char **, FILE *, FILE *);
int add_character_to_byte(FILE *, int, int *, int);
TreeNode *build_tree(ListNode *);
char **build_table(TreeNode *);
long count_char_frequency(FILE *, int *);
int add_one_to_byte (int, int);
void delete_table(char **);
