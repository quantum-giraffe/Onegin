#include <iostream>
#include <cstdio>
#pragma warning(disable : 4996)

using namespace std;

/*
���� ��������� ��������� �������� ������ ��������� ����� (�� ������� '\r') [����� EOF?]
������� ���������
���������� �� ���������� � ������� ��� ����������
�������� �������������� ��� ������
*/


int n_str(char buf[], int size)  //��������� ���������� ����� � �������� '\n' �� '\0' 
{
	int n = 1;
	for (int i = 0; i < size; i++) {
		if (buf[i] == '\n') {
			buf[i] = '\0';
			if(buf[i+1])
			n++;
		}
	}
	return n;
}

void fill_text(char buf[], char* text[], int size, int n) //��������� ������ text[]
{
	text[0] = &buf[0];
	for (int i = 1, j = 1; i < size && j <n; i++) {
		if (buf[i] == '\0') {
			text[j] = &buf[i]+1;
			cout << j << "    ";
			for (int e = 0; *(text[j] + e) != '\0'; e++) {
				cout << *(text[j]+e);
			}
			cout << endl;
			j++;
		}
	}
}

//void Sort(char* text[], int n) 
//{
//	for (int k = 0; k < n-1; k++) {
//		for (int i = k + 1; i < n-1; i++) {
//			int j = 0;
//			char a = '1';
//			char b = '1';
//			do {
//				a = *(text[k] + j);
//				b = *(text[i] + j);
//				j++;
//				if (b < a) {
//					char* tmp = text[i];
//					text[i] = text[k];
//					text[k] = tmp;
//					break;
//				}
//			} while (a != '\0' && b != '\0');
//		}
//		if (!isupper(*(text[k] + 2)) && *text[k] != '\0') //����������� ������� ������ (�������� � �� ���������)
//			puts(text[k]);
//	}
//}

int CompareStr(const void* left, const void* right)
{
	return strcmp(*(char**)left, *(char**)right);
}

void PrintText(char buf[], int size)
{
	int t = 1;
	cout << t << "    ";
	for (int i = 0; i < size; i++) {
		cout << buf[i];
		if (buf[i] == '\0') {
			cout << endl << t + 1 << "    ";
			t++;
		}
	}
}

int main()
{
	FILE * input = fopen("Hamlet.txt", "r");
	if (!input) return 1;
	fseek(input, 0, SEEK_END);
	int size = ftell(input)+1;  //���������� ������ �� 5590 ����� ������, ��� ������. 5590 - ��� ����� ���������� �����
	cout << size << endl;       //������, ��� '\r' . ���� ���-�� ����������� �� ��� �� ������ �������� ��������
	size = 175090;
	char* buf = (char*)calloc(size, sizeof(char)); //��������� ������ ��� �����
	if (buf == NULL) return 2;
	rewind(input);
	fread(buf, 1, size, input);
	int n = n_str(buf, size);
//	if (n != 5590) return n;
	PrintText(buf, size);
	char** text = (char**)calloc(n, sizeof(int));   //��������� ������ ��� ������ ����������
	if (text == NULL) return 3;
	fill_text(buf, text, size, n);
	qsort(text, n, sizeof(*text), CompareStr);
//	Sort(text, n);                               //������ ������� ����������
	for (int i = 0; i < n; i++) {
		if (!isupper(*(text[i] + 2)) && *text[i] != '\0') //����������� ������� ������ (�������� � �� ���������)
			cout << i + 1 << "   ";
			puts(text[i]);
	}
	free(buf);
	free(text);
	fclose(input);

	system("pause");
	return 0;
}