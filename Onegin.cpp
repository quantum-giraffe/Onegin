#include <iostream>
#include <cstdio>
#include <cstdlib>
#pragma warning(disable : 4996)

using namespace std;

/* Плохо работает проверка строк на нормальность */

//int A = 0;

struct line
{
	char* str;
	int len = 0;
};

int n_str(char buf[], int& size)  //вычисляет количество строк, пересчитывает количество символов, заменяет '\n' на '\0' 
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
//			printf("%d    %s\n", j, text[j - 1].str);
			j++;
		}
	}
//	printf("%d    %s\n", n, text[n-1].str);
}

int CompareStr(const void* left_0, const void* right_0)
{
//	extern int A;
//	A++;
	
	line left = *(line*)left_0;
	line right = *(line*)right_0;
	if (left.len == right.len) {
		for (int i = 0, j = 0; i < left.len, j < right.len; i++, j++) {
			while ((ispunct(left.str[i])  || isspace(left.str[i]))  && left.str[i]  != '\0') i++;
			while ((ispunct(right.str[j]) || isspace(right.str[j])) && right.str[j] != '\0') j++;
			if (left.str[i] != right.str[j]) 
//				printf("%d    '%c'    %d\n", A, left.str[i], left.str[i] - right.str[j] );
				return (left.str[i] - right.str[j]);
		}
	}
	else {
//		printf("%d            %d\n", A, left.len - right.len);
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
//		if (!isupper(*(text[i].str + 2)) && (!isspace(*text[i].str))) //определение обычной строки (непустой и не заголовка)
//		{
			printf("%d    ", i + 1);
			puts(text[i].str);
//		}
	}
}

int main()
{
	FILE * input = fopen("Hamlet.txt", "r");
	if (!input) return 1;
	fseek(input, 0, SEEK_END);
	int size = ftell(input) + 1; 
//	printf("%d\n", size); 
	char* buf = (char*)calloc(size, sizeof(char)); //выделение памяти под буфер
	if (buf == NULL) return 2;
	rewind(input);
	fread(buf, 1, size, input);
	int n = n_str(buf, size);
//	printf("%d\n%d\n", size, n);
//	PrintBuf(buf, size);
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