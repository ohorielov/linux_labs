#include <stdio.h>

int main()
{
    char *filename = "non_compressed_text.txt";
    FILE *inputfile = fopen(filename, "r");

    if (inputfile == NULL)
    {
        printf("Can not open file %s", filename);
        return 1;
    }
    FILE *outputfile = fopen("nnnnnnn.txt", "w");
    return 0;
}
