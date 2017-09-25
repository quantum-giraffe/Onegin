#include <iostream>
#include <cstdio>
#pragma warning(disable : 4996)

using namespace std;

/*
Надо научиться правильно измерять размер вводимого файла (не считать '\r') [может EOF?]
Создать Структуру
Улучшить форматирование при выводе
*/


int n_str(char buf[], int& size)  //вычисляет количество строк и заменяет '\n' на '\0' 
{
	int n = 1;
	int i = 0;
	for (int q = 0; q < size; i++, q++) {
		if (buf[i] == '\n') {
			buf[i] = '\0';
			q++;
			if (buf[i + 1])
				n++;
		}
	}
	buf[i-1] = '\0';
	buf[i] = EOF;
	size = i - 1;
	return n;
}

void fill_text(char buf[], char* text[], int size, int n) //заполняет массив text[]
{
	text[0] = &buf[0];
	for (int i = 1, j = 1; i < size && j <n; i++) {
		if (buf[i] == '\0') {
			text[j] = &buf[i+1];
//			printf("%d    %s\n", j, *text[j]);
			text[j] = &buf[i] + 1;
			printf("%d    ", j+1);
			for (int e = 0; *(text[j] + e) != '\0'; e++) {
				printf("%c", *(text[j] + e));
			}
			printf("\n");
			j++;
		}
	}
}

int CompareStr(const void* left_0, const void* right_0)
{
	const char* left = *(char**)left_0;
	const char* right = *(char**)right_0;
	while (ispunct(*left) || isspace(*left)) left++;
	while (ispunct(*right) || isspace(*right)) right++;
	return strcmp(left, right);
}

void PrintBuf(char buf[], int size)
{
	int t = 1;
	printf("%d    ", t);
	for (int i = 0; i < size; i++) {
		printf("%c", buf[i]);
		if (buf[i] == '\0') {
			printf("\n%d    ", t + 1);
			t++;
		}
	}
}

void PrintText(char* text[], int n)
{
	for (int i = 0; i < n; i++) {
		if (!isupper(*(text[i] + 2)) && *text[i] != '\0') //определение обычной строки (непустой и не заголовка)
			printf("%d    ", i + 1);
		puts(text[i]);
	}
}

int main()
{
	FILE * input = fopen("Hamlet.txt", "r");
	if (!input) return 1;
	fseek(input, 0, SEEK_END);
	int size = ftell(input) + 1; 
	printf("%d\n", size); 
	char* buf = (char*)calloc(size, sizeof(char)); //выделение памяти под буфер
	if (buf == NULL) return 2;
	rewind(input);
	fread(buf, 1, size, input);
	int n = n_str(buf, size);
	printf("%d\n%d\n", size, n);
	PrintBuf(buf, size);
	char** text = (char**)calloc(n, sizeof(int));   //выделение памяти под массив указателей
	if (text == NULL) return 3;
	fill_text(buf, text, size, n);
	qsort(text, n, sizeof(*text), CompareStr);
	PrintText(text, n);
	free(buf);
	free(text);
	fclose(input);

	system("pause");
	return 0;
}