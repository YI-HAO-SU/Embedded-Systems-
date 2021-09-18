// thread.cpp : 定義主控台應用程式的進入點。
//

#include "pch.h"
#include <stdlib.h>

#include <stdio.h>	
#include <string.h>	
#include <time.h>
#include <sys/stat.h>
#include <conio.h>
#include <fstream>
#include <direct.h>
#include <iostream>
#include <sys/timeb.h>
#include <time.h>
#include <process.h>

using namespace std;
#include <WINSOCK2.H>
#pragma comment(lib, "wsock32.lib")
using namespace std;
#include <Windows.h>

#include <TimeAPI.h>
#pragma comment(lib, "Winmm.lib")

#if defined(_MSC_VER) || defined(_MSC_EXTENSIONS)
#define DELTA_EPOCH_IN_MICROSECS  11644473600000000Ui64
#else
#define DELTA_EPOCH_IN_MICROSECS  11644473600000000ULL
#endif
void GotoXY(SHORT x, SHORT y);
void GetXY(int* x, int* y);

void clock_1sec(void* p);
int TestAndSet(void);
void ReleaseTAS(void);
void printMsg(char* msg);
void getLocalTimeLog(char* cctime);
void clock_1ms(void* p);

/////////////////////////////////////////////////////////////////////////////////
//功能撰寫
struct BufNode {
	char buf[100];
	struct BufNode* nptr, * fptr;
};

struct BufNode* getnode(void);
/*char* get_buf(void);*/
char append_char_to_string(struct BufNode* s, char c);
void print_string(char* buft);
char delete_char_string(struct BufNode* s);

struct BufNode* getnode(void) {
	struct BufNode* ptr;
	ptr = (struct BufNode*)malloc(1 * sizeof(struct BufNode));
	ptr->fptr = ptr->nptr = NULL;						//Initialize
	(ptr->buf)[0] = 0x00;
	return ptr;
}
/////////////////////////////////////////////////////////////////////////////////

int eflag = 0;
int tcount = 0;

int main(void)
{
	char msg[100];
	char c;

	struct BufNode* tbuf, * ubuf;
	tbuf = ubuf = getnode();

	timeBeginPeriod(1);
	eflag = 1;
	strcpy_s(msg, "-------------------------------------------------");
	_beginthread(clock_1sec, 0, msg);
	_beginthread(clock_1ms, 0, msg);
	Sleep(10);
	printf("%s\n", msg);
	c = 0;
	while ( (c= _getch()) != 0x1B) {
		switch (c) {
		case '-': {															//- Close Clock
			eflag = 0;
			break;
		}
		case 0x08:														//Backspace
		{
			putchar(c);													//Backspace
			putchar(' ');													//print ' ' cover the last text
			putchar(c);													//Backspace
			int flag = delete_char_string(ubuf);			//
			if (flag == 0)												//
				putchar(0x07);											//BEBE       //BUG : only the first row will success , if enter to next row happen nothing 
			break;															//out of the loop
		}
		case 0x0D:														//Enter
		{
			putchar(c);													//enter 
			putchar(0x0A);											//換行
			append_char_to_string(ubuf, 0x0A);
			break;
		}
		case 0x1B:														//ese      All Close
		{														
			break;
		}
		case '+': {														//+
			putchar(0x08);
			putchar(' ');
			timeBeginPeriod(1);
			eflag = 1;
			strcpy_s(msg, "Hello!!");
			printf("\n===Thread Open [clock_1sec]===\n");

			_beginthread(clock_1sec, 0, msg);
			_beginthread(clock_1ms, 0, msg);

		}
		default:
			putchar(c);
			append_char_to_string(ubuf, c);
		}

	}
}


void clock_1sec(void* p)
{
	char tt[100];
	int tcount_old;
	int xs, ys;//
	printf("%s\n", (char*)p);
	strcpy((char*)p, "Function [ + Open Time Again ] [ - Close Time ] [ esc OVER ] [ backspace ] [ Enter ] ");
	tcount_old = tcount;
	while (eflag) {
		Sleep(1);
		if ((tcount - tcount_old) <= 500) continue;
		tcount_old = tcount;

		getLocalTimeLog(tt);

		GetXY(&xs, &ys);
		GotoXY(65, 1);
		printf("[%s]", tt);
		GotoXY(xs, ys);
	}
	printf("\n===Thread Exit [clock_1sec]===\n");
	_endthread();
}
void clock_1ms(void* p)
{
	printf("Now Time is ===============================>\n");
	while (1) {
		Sleep(1);
		tcount++;
	}
	_endthread();
}
void getLocalTimeLog(char* cctime)
{
	time_t timer;
	struct tm* tblock;

	timer = time(NULL);
	tblock = localtime(&timer);
	sprintf(cctime, "%d/%02d/%02d %02d:%02d:%02d", (tblock->tm_year + 1900) - 1911, tblock->tm_mon + 1, tblock->tm_mday, tblock->tm_hour, tblock->tm_min, tblock->tm_sec);
}

//=====================================================================
// Set current cursor position.
void GotoXY(SHORT x, SHORT y)
{
	// Set the cursor position.
	HANDLE StdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD Cord;
	Cord.X = x;
	Cord.Y = y;
	SetConsoleCursorPosition(StdOut, Cord);
}
void GetXY(int* x, int* y)
{
	// Set the cursor position.
	HANDLE StdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO ScreenBufferInfo = { 0 };
	GetConsoleScreenBufferInfo(StdOut, &ScreenBufferInfo);


	*x = ScreenBufferInfo.dwCursorPosition.X;
	*y = ScreenBufferInfo.dwCursorPosition.Y;

}

/////////////////////////////////////////////////////////////////////////////////////////////////

char delete_char_string(struct BufNode* s) {
	int i = 0;
	struct BufNode* t = s;
	while ((s->buf)[i]) {
		i++;
		if (i == 100) {
			s = s->nptr;
			i = 0;
		}
	}
	if (i == 0) {
		struct BufNode* t = s;
		s = s->fptr;
		if (s == NULL) {											//When last one already NULL can not delete any more
			s = t;														//already the first one
			i = 0;														//set i to 0
			return 0;													//return s to 0
		}
		else {
			free(t);														//release t cause useless 清空ptr不然會一直占用新的空間
			i = 99;														//set i to 99
			s->nptr = NULL;									//????????????????
		}
	}
	else {
		i--;																// i != 0 direct i--
	}
	(s->buf)[i] = 0x00;										//set buf[i] as 0
	return 1;
}

char append_char_to_string(struct BufNode* s, char c) {
	int i = 0;
	struct BufNode* t = s;

	while ((s->buf)[i]) {
		i++;
		if (i == 100) {
			s = s->nptr;													//buf load buf[100]  
			i = 0;															//i return to 0
		}
	}
	(s->buf)[i++] = c;												//buf[i++] = c
	if (i == 100) {
		struct BufNode* t = s;										//t load buf
		s = s->nptr = getnode();									//buf value = { get_buf() } return  s
		s->fptr = t;														//讓temp保留原本ptr儲存的前一組的位址資料
		i = 0;
	}
	(s->buf)[i] = 0x00;												//set buf[i] as 0
	return c;
}

void print_string(struct BufNode* buft) {
	int i = 0;
	while ((buft->buf)[i])
	{
		putchar((buft->buf)[i++]);
		if (i == 100)
		{
			buft = buft->nptr;
			i = 0;
		}
	}
}