#define MAP_SIZE 5000
#define ll unsigned long long 

typedef struct HashNode {
    ll code;
    ll size;
    char encodedChar;
    struct HashNode* next;
} HashNode;

typedef struct HashMap{
    HashNode* HashArr[MAP_SIZE];
} HashMap;

void initMap(HashMap* mp);
void insertMap(HashMap*, ll, ll, char);
int findMap(HashMap, ll, ll);
