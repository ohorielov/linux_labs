#include <stdio.h>
#include <string.h>

//структура, що використовується для визначення вузла
typedef struct node_t {
	struct node_t* left, * right;
	int freq;
	char c;
} *node;

int n_nodes = 0, qend = 1; 	//глобальні змінні для відстеження кількості вузлів і кінця черги
struct node_t pool[256] = { {0} }; //пул вузлів     
node qqq[255], * q = qqq - 1;    //масив рядків кодів для кожної літериіоритетна черга
char* code[128] = { 0 }, buf[1024];	
int input_data = 0, output_data = 0;

//функція, що використовується для створення нового вузла
node new_node(int freq, char c, node a, node b)
{
	node n = pool + n_nodes++;
	if (freq != 0) {
		n->c = c;	//присвоїти символ 'c' символу вузла (зрештою листка)	
		n->freq = freq;	//призначити частоту	 
	}
	else {
		n->left = a, n->right = b; //якщо не вказано частоту виклику
		n->freq = a->freq + b->freq;	//вилучені вузли в кінці черги будуть додані ліворуч і праворуч
	}
	return n;
}
//функція, що використовується для вставлення вузла в пріоритетну чергу
void qinsert(node n)
{
	int j, i = qend++;
	while ((j = i / 2)) {
		if (q[j]->freq <= n->freq) 
			break;
		q[i] = q[j], i = j;
	}
	q[i] = n;
}

node qremove()
{
	int i, l;
	node n = q[i = 1];

	if (qend < 2) return 0;
	qend--;
	while ((l = i * 2) < qend) {
		if (l + 1 < qend && q[l + 1]->freq < q[l]->freq) l++;
		q[i] = q[l], i = l;
	}
	q[i] = q[qend];
	return n; //повернути вузол
}
//пройти уздовж побудованого дерева Хаффмана та призначити код для кожного символу
void build_code(node n, char* s, int len)
{
	static char* out = buf;
	if (n->c) {
		s[len] = 0;	 //якщо наданий вузол є листом (кінцевий вузол)
		strcpy(out, s);		// містить символ
		code[(int)n->c] = out;	// тому код копіюється у відповідний символ.
		out += len + 1;//вихідний показник збільшується
		return;
	}

	s[len] = '0'; build_code(n->left, s, len + 1); //повторювано використовується для написання коду
	s[len] = '1'; build_code(n->right, s, len + 1);
}

void import_file(FILE* fp_in, unsigned int* freq) {
	char c, s[16] = { 0 };		
	int i = 0;
	printf("File input :");
	while ((c = fgetc(fp_in)) != EOF) {
		freq[(int)c]++;		 //читати файл символ за символом і збільшувати певну частоту символу
		putchar(c);
	}
	for (i = 0; i < 128; i++)
		if (freq[i]) qinsert(new_node(freq[i], i, 0, 0)); //вставити нові вузли в чергу, якщо є частота
	while (qend > 2)
		qinsert(new_node(0, 0, qremove(), qremove())); // побудувати дерево
	build_code(q[1], s, 0); //будуємо код для символів
}

void encode(FILE* fp_in, FILE* fp_out, unsigned int* freq) {

	char in, c, temp[20] = { 0 };
	int i, j = 0, k = 0, lim = 0;
	rewind(fp_in);
	for (i = 0; i < 128; i++) {
		if (freq[i])	lim += (freq[i] * strlen(code[i]));
	}
	output_data = lim;		//Вихідні дані дорівнюють верхній межі ліміту
	fprintf(fp_out, "%04d\n", lim);
	printf("\nEncoded:\n");
	for (i = 0; i < lim; i++) {
		if (temp[j] == '\0') {
			in = fgetc(fp_in);
			strcpy(temp, code[in]);
			printf("%s", code[in]);
			j = 0;
		}
		if (temp[j] == '1')
			c = c | (1 << (7 - k));   //зміщує 1 у відповідну позицію та АБО з тимчасовим символом
		else if (temp[j] == '0')
			c = c | (0 << (7 - k));  //зміщує 0 у відповідну позицію та OR з тимчасовим символом
		else
			printf("ERROR: Wrong input!\n");
		k++;    // k використовується для поділу рядка на 8-бітові фрагменти та збереження 
		j++;
		if (((i + 1) % 8 == 0) || (i == lim - 1)) {
			k = 0;             //скинути k  
			fputc(c, fp_out);     //збереження символу
			c = 0;               //скинути символ
		}
	}
	putchar('\n');
}

void print_code(unsigned int* freq) {
	int i;
	printf("\nChar frequency code :\n");
	for (i = 0; i < 128; i++) {
		if (isprint((char)i) && code[i] != NULL && i != ' ')
			printf("%-4c  %-4d  %16s\n", i, freq[i], code[i]);
		else if (code[i] != NULL) {
			switch (i) {
			case '\n':
				printf("\\n  ");
				break;
			case ' ':
				printf("\' \' ");
				break;
			case '\t':
				printf("\\t  ");
				break;
			default:
				printf("%0X  ", (char)i);
				break;
			}
			printf("  %-4d  %16s\n", freq[i], code[i]);
		}
	}
	printf("----------------------------\n");

}

int main() {
	FILE* fp_in, * fp_out;	//Вказівники FIFO			
	char file_name[100] = { 0 };	//назва файлу			
	unsigned int freq[128] = { 0 }, i;	//частота літер

	strcpy(file_name, "non_compressed_text.txt");

	//імпорт файлу у програму та оновлення дерева Хаффмана
	if ((fp_in = fopen(file_name, "r")) == NULL) {
		printf("\nERROR: No such file\n");
		return 0;
	}
	import_file(fp_in, freq);//імпортувати файл і заповнювати масив частот


	print_code(freq);				//друк кодової таблиці
	fp_out = fopen("compressed_text.txt", "w");	//закодований файл зберігається в розширенні .txt
	encode(fp_in, fp_out, freq);

	fclose(fp_in);
	fclose(fp_out);

	strcpy(file_name, "compressed_text.txt");	//записати таблицю частот у розширенні .txt
	fp_out = fopen(file_name, "w");
	for (i = 0; i < 128; i++) {
		fprintf(fp_out, "%c", (char)freq[i]); //записати частоту у файл
	}

	for (i = 0; i < 128; i++)	input_data += freq[i];	//обчислити вхідні байти

	fclose(fp_out);			//закрити вказівник вихідного файлу		
	printf("\nInput bytes:\t\t%d\n", input_data);
	output_data = (output_data % 8) ? (output_data / 8) + 1 : (output_data / 8);
	printf("Output bytes:\t\t%d\n", output_data);

	printf("Compression ratio:\t%.2f%%\n", ((double)(input_data - output_data) / input_data) * 100);
	return 0;
}
