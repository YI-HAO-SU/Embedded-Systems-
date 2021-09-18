#include "pch.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include "ShowMessage.h"
void printmsg(char* s);
void GotoXY(SHORT x, SHORT y);
void GetXY(int* x, int* y);
static char* msg[10];
static SHORT x0, y0;
static int n = 0;
static int LB ;												//Define reorganization row 
void initShowMsg(SHORT x, SHORT y,int LBR)
{
	int i;
	LB = LBR;
	for (i = 0; i < LB; i++) {
		msg[i] = (char*)malloc((40 + 1) * sizeof(char));
	}
	x0 = x;
	y0 = y;
	n = 0;
}
void ClrMsg(int LBR)
{
	int i;
	int x, y;
	LB = LBR;

	GetXY(&x, &y);
	for (i = 0; i < LB; i++) {
		GotoXY(x0, y0 + i);
		msg[i][0] = 0x00;
		printmsg(msg[i]);
	}
	n = 0;
	GotoXY(x, y);
}
void show_msg(char* msgs,int LBR)
{
	static int n = 0;
	int x, y;
	int i;
	char* ptr;
	LB = LBR;

	GetXY(&x, &y);
	if (n < LB) {
		strcpy_s(msg[n], 40, msgs);
		GotoXY(x0, y0 + n);
		printmsg(msg[n]);
		n++;
	}
	else {
		ptr = msg[0];
		for (i = 0; i < n; i++) {
			msg[i] = msg[i + 1];
		}

		msg[n - 1] = ptr;
		strcpy_s(msg[n - 1], 40, msgs);
		for (i = 0; i < n; i++) {
			GotoXY(x0, y0 + i);
			printmsg(msg[i]);
		}
	}
	GotoXY(x, y);
}
void printmsg(char* s)
{
	int i;
	for (i = 0; s[i] && i < 40; i++) {

		if (s[i] != '\n')putchar(s[i]);
		else putchar(' ');
	}
	for (; i < 40; i++) {
		putchar(' ');
	}
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