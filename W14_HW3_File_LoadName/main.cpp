#include "pch.h"
#include<stdio.h>
#include<iostream>
using namespace std;
void printName(char*** Name);
int putStr(char* s);
void putstrH(char* s, int n);
void printNameT(char*** Name);
int clearCR_LF(char* s);
int main(void)
{
	FILE* fp;
	char buf[101];
	int n, i, j;
	char*** Name, c;

	//修改從Name.txt檔案讀入Name
	Name = (char***)malloc(5 * sizeof(char**));							//可讀取字數
	for ( i = 0; i < 5; i++)																	//Initialize
	{
		Name[i] = NULL;
	}
	for ( i = 0; i < 3; i++)														
	{
		Name[i] = (char**)malloc(15 * sizeof(char*));						//每一字數佔幾列
	}
	fopen_s(&fp, "Name.txt", "rb");													//讀取
	if (fp == NULL) {																		//找不到
		printf("[%s] can not find! \n%c", "Name.txt", 0x07);
		exit(0);
	}
	for ( i = 0; i < 3; i++)
	{
		for (j = 0; j < 15; j++) {
			Name[i][j] = (char*)malloc(101 * sizeof(char));				//每列上限100字元 +1因為字串界符
			fgets(Name[i][j], 100, fp);
			clearCR_LF(Name[i][j]);									

		}
		Name[i][j] = NULL;																 //每個NAME的最後一列為NULL
	}
	fclose(fp);

	printName(Name);
	printNameT(Name);
}
void printName(char*** Name)
{
	int i, j;
	for (i = 0; Name[0][i] != NULL; i++) {
		for (j = 0; Name[j]; j++) {
			putStr(Name[j][i]);
			putchar('\t');
		}
		putchar('\n');
	}

}

void printNameT(char*** Name)
{
	int i, j;
	char T[5];
	T[0] = 0x00;
	for (i = 0; Name[i] != NULL; i++) {			//使每個字前有幾個TAB
		for (j = 0; Name[i][j]; j++) {
			printf("%s", T);
			putStr(Name[i][j]);
			putchar('\n');
		}
		T[i] = '\t';
		T[i + 1] = 0x00;
	}

}

int putStr(char* s)
{
	int i;
	for (i = 0; s[i]; i++) {
		putchar(s[i]);
	}
	//	putchar('\n');
	return i;
}
void putstrH(char* s, int n)
{
	int i;
	for (i = 0; i < n; i++)
		printf("%02X ", (unsigned char)s[i]);
	putchar('\n');
}
int clearCR_LF(char* s)
{
	int i, j = 0;
	//修改去除CR(0x0D) LF(0x0A)
	for (i = 0; s[i]; i++) {
		if (s[i] == 0x0D || s[i] == 0x0A){
			continue;
		}
		s[j++] = s[i];
	}
	s[j] = 0x00;
	return j;
}