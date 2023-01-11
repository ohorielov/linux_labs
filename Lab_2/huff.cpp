#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#ifndef NULL
#define NULL   ((void *) 0)
#endif

#define ascisymb  128

int nodes = 0;
char *codelist[ascisymb] = {0}, buffer[1024];

typedef struct Node {
	char symb;
	int freq;
	struct Node *left, *right;
} *node;

int endquery = 1;
struct Node pool[ascisymb] = {{0}};
node priority_que[ascisymb-1], *q = priority_que-1;

node create_node(int freq, char c, node l, node r)
{
	node nod = pool + nodes++;
	if (freq != 0){
		nod->symb = c;
		nod->freq = freq;
	}
	else {
		nod->left = l;
		nod->right = r;
		nod->freq = l->freq + r->freq;
	}
	return nod;
}

void insert_node(node nod)
{
	int j, i;
	i = endquery++;

	while ((j = i / 2)) {
		if (q[j]->freq <= nod->freq)
			break;
		q[i] = q[j], i = j;
	}
	q[i] = nod;
}

node get_from_que()
{
	int i, j;
	node nod = q[i = 1];

	if (endquery < 2)
		return 0;
	endquery--;

	while ((j = i * 2) < endquery) {

		if (j + 1 < endquery && q[j + 1]->freq < q[j]->freq)
			j++;
		q[i] = q[j], i = j;
	}
	q[i] = q[endquery];
	return nod;
}


void create_codelist(node nod, char *s, int len)
{
	static char *let = buffer;

	if (nod->symb) {
		s[len] = 0;
		strcpy(let, s);
		codelist[(int)nod->symb] = let;
		let += len + 1;
		return;
	}

	s[len] = '0'; create_codelist(nod->left,  s, len + 1);
	s[len] = '1'; create_codelist(nod->right, s, len + 1);
}

void read_file(FILE *file, unsigned int *freq){
	char c,s[16]={0};
	int i = 0;

	printf("File Read:\n");

	while((c=fgetc(file)) != EOF){
        freq[(int)c]++;
		putchar(c);
	}
	for (i = 0; i < ascisymb; i++)
		if (freq[i])
			insert_node(create_node(freq[i], i, 0, 0));

	while (endquery > 2)
		insert_node(create_node(0, 0, get_from_que(), get_from_que()));

	create_codelist(q[1], s, 0);
}

void print_codes(unsigned int *freq){
int i;
printf("\n");
	for( i=0; i<ascisymb; i++){

		if(codelist[i]!=NULL && i!=' ' && i!='\n' && i!='\0')
			printf("%c  %d  %s\n",i,freq[i],codelist[i]);

		else if(codelist[i]!=NULL){
			switch(i){
				case '\n':
					printf("enter");
					break;
				case '\0':
					printf("end of line");
					break;
				case ' ':
					printf("space");
					break;
				default:
					printf("%0X  ",(char)i);
					break;
			}
			printf("  %d  %16s\n",freq[i],codelist[i]);
		}
	}
}

void encode(FILE* fil_in, FILE* fil_out, unsigned int *freq ){

	char in,c,temp[20] = {0};
	int i, j = 0,k = 0,limit = 0;

	rewind(fil_in);

	for(i=0; i<ascisymb; i++)
		if(freq[i])
			limit += (freq[i]*strlen(codelist[i]));


	fprintf(fil_out,"%d\n",limit);
	printf("\n %d \n", limit);

	for(i=0; i<limit; i++){
		if(temp[j] == '\0'){
			in = fgetc(fil_in);
			strcpy(temp,codelist[in]);
			printf("%s",codelist[in]);
			j = 0;
		}
		if(temp[j] == '1')
			c = c|(1<<(7-k));
        else if(temp[j] == '0')
        	c = c|(0<<(7-k));
        k++;
		j++;

		if(((i+1)%8 == 0) || (i==limit-1)){
            fputc(c,fil_out);
            c = 0;
            k = 0;
        }
	}
	fclose(fil_out);
}

void read_table(FILE *table, unsigned int *freq){
	char c;
	int i = 0;

	while((c=fgetc(table))!=EOF)
		freq[i++] = (unsigned char)c;

	for (i = 0; i < ascisymb; i++)
		if (freq[i])
			insert_node(create_node(freq[i], i, 0, 0));

	while (endquery > 2)
		insert_node(create_node(0, 0, get_from_que(), get_from_que()));
}

void decode(FILE *fil_in,FILE *fil_out){
	int i = 0,limit = 0,j = 0;
	char c;
	node nod = q[1];

	fscanf(fil_in,"%d",&limit);
	fseek(fil_in,1,SEEK_CUR);
	printf("\n Decode: \n");

	for(i=0; i<limit; i++){
		if(j==0)
			c = fgetc(fil_in);

		if(c&ascisymb)
			nod = nod->right;
		else
			nod = nod->left;

		if(nod->symb){
			putchar(nod->symb);
            fputc(nod->symb,fil_out);
            nod = q[1];
        }
		c = c<<1;
		if(++j>7)
			j = 0;
	}
	putchar('\n');
	if (q[1] != nod)
		printf("err\n");
}

int main(int argc, char* argv[]){

    FILE* file_input, * file_encode,*table, * file_decode;
	unsigned int freq[ascisymb] = {0};

	char const* inputFileName;
	inputFileName = "noncompressedtext.txt";
	file_input = fopen(inputFileName,"r");
	read_file(file_input,freq);

	print_codes(freq);

	char const* tableFileName;
	tableFileName = "encodetable.table";

	table = fopen(tableFileName,"w+");
	for(int i=0; i<ascisymb; i++){
		fprintf(table, "%c", (char)freq[i] );
	}
	fclose(table);

	char const* encodeFileName;
	encodeFileName = "compressedtext.txt";
	file_encode = fopen(encodeFileName,"w+");
	encode(file_input,file_encode,freq);

	fclose(file_input);

	unsigned int freqdec[ascisymb] = {0};

	file_encode = fopen(encodeFileName, "r");
	table = fopen(tableFileName, "r");

	nodes = 0, endquery = 1;

	read_table(table, freqdec);

	char const* decodeFileName;
	decodeFileName = "decodetext.txt";
	file_decode = fopen(decodeFileName, "w+");

	decode(file_encode, file_decode);

	fclose(file_decode);
	fclose(file_encode);
	fclose(table);

	return 0;
}
