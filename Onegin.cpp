#include <iostream>
#include <cstdio>
#pragma warning(disable : 4996)

using namespace std;

/*
Надо научиться правильно измерять размер вводимого файла (не считать '\r') [может EOF?]
Создать Структуру
Улучшить форматирование при выводе
*/

int A = 0;

struct line
{
	char* str;
	int len;
};

int n_str(char buf[], int size)  //вычисляет количество строк и заменяет '\n' на '\0' 
{
	int n = 1;
	for (int i = 0; i < size; i++) {
		if (buf[i] == '\n') {
			buf[i] = '\0';
			if (buf[i + 1])
				n++;
		}
	}
	return n;
}

void fill_text(char buf[], line text[], int size, int n) //заполняет массив text[]
{
	text[0].str = &buf[0];
	int sum_len = 0;
	for (int i = 1, j = 1; i < size && j < n + 1; i++) {
		if (buf[i] == '\0') {
			text[j].str = &buf[i] + 1;
			if (j == 1) 
				text[j - 1].len = i;
			else 
				text[j - 1].len = i - sum_len;
			sum_len += text[j - 1].len;
			printf("%d    %s\n", j, text[j - 1].str);
			j++;
		}
	}
	printf("%d    %s\n", n, text[n-1].str);
}

int CompareStr(const void* left_0, const void* right_0)
{
	extern int A;
	A++;
	
	line left = *(line*)left_0;
	line right = *(line*)right_0;
	if (left.len == right.len) {
		for (int i = 0, j = 0; i < left.len, j < right.len; i++, j++) {
			while (ispunct(left.str[i]) || isspace(left.str[i])) {
				i++;
			}
			while (ispunct(right.str[i]) || isspace(right.str[i])) {
				j++;
			}
			if (left.str[i] != right.str[j]) 
				printf("%d    %5s  :  %5s\n", A, left.str, right.str );
				return (left.str[i] - right.str[j]);
		}
	}
	else {
		printf("%d    %5s  :  %5s\n", A, left.len, right.len);
		return (left.len - right.len);
	}
	return 0;
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
	printf("\n");
}

void PrintText(line text[], int n)
{
	for (int i = 0; i < n; i++) {
		if (!isupper(*(text[i].str + 2)) && (text[i].str != '\0')) //определение обычной строки (непустой и не заголовка)
			printf("%d    ", i + 1);
		puts(text[i].str);
	}
}

int main()
{
	FILE * input = fopen("Hamlet.txt", "r");
	if (!input) return 1;
	fseek(input, 0, SEEK_END);
	int size = ftell(input) + 1;  //выделяется память на 5590 ячеек больше, чем должно. 5590 - это ровно количество строк
	printf("%d", size);      //видимо, это '\r' . Надо как-то избавляться от них на стадии подсчета символов
	size = 175090;
	printf("%d", size);
	char* buf = (char*)calloc(size, sizeof(char)); //выделение памяти под буфер
	if (buf == NULL) return 2;
	rewind(input);
	fread(buf, 1, size, input);
	int n = n_str(buf, size);
	PrintBuf(buf, size);
	line* text = (line*)calloc(n, sizeof(line));   //выделение памяти под массив указателей
	if (text == NULL) return 3;
	fill_text(buf, text, size, n);
	qsort(text, n, sizeof(line), CompareStr);
	PrintText(text, n);
	free(buf);
	free(text);
	fclose(input);

	system("pause");
	return 0;
}