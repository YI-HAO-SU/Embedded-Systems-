#include "pch.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include "ShowMsg.h"
void printmsg(char * s);
void GotoXY(SHORT x, SHORT y);
void GetXY(int * x, int * y);
static char *msg[10];
static SHORT x0, y0;
static int n = 0;

//Chat
typedef struct {
	char* msg[10];
	SHORT x0, y0;
	int n = 0;
}msgPlan;
static msgPlan mp[10];
static int LB;
void initShowMsg_C(int id, SHORT x, SHORT y, int LBR)
{
	int i;
	LB = LBR;
	for (i = 0; i < LB; i++) {
		mp[id].msg[i] = (char*)malloc((40 + 1) * sizeof(char));
	}
	mp[id].x0 = x;
	mp[id].y0 = y;
	mp[id].n = 0;
}
void ClrMsg_C(int  id, int LBR)
{
	int i;
	int x, y;
	LB = LBR;

	GetXY(&x, &y);
	for (i = 0; i < LB; i++) {
		GotoXY(mp[id].x0, mp[id].y0 + i);
		mp[id].msg[i][0] = 0x00;
		printmsg(mp[id].msg[i]);
	}
	mp[id].n = 0;
	GotoXY(x, y);
}
void show_msg_C(int id, char* msgs, int LBR)
{
	int x, y;
	int i;
	char* ptr;
	LB = LBR;

	GetXY(&x, &y);
	if (mp[id].n < LB) {
		strcpy_s(mp[id].msg[mp[id].n], 40, msgs);
		GotoXY(mp[id].x0, mp[id].y0 + mp[id].n);
		printmsg(mp[id].msg[mp[id].n]);
		mp[id].n++;
	}
	else {
		ptr = mp[id].msg[0];
		for (i = 0; i < mp[id].n; i++) {
			mp[id].msg[i] = mp[id].msg[i + 1];
		}

		mp[id].msg[mp[id].n - 1] = ptr;
		strcpy_s(mp[id].msg[mp[id].n - 1], 40, msgs);
		for (i = 0; i < mp[id].n; i++) {
			GotoXY(mp[id].x0, mp[id].y0 + i + id * 10);
			printmsg(mp[id].msg[i]);
		}
	}
	GotoXY(x, y);
}
//OX
void initShowMsg(SHORT x, SHORT y)
{
	int i;
	for (i = 0;i < 10;i++) {
		msg[i] = (char *)malloc((40+1) * sizeof(char));
	}
	x0 = x;y0 = y;n = 0;
}
void ClrMsg(void)
{
	int i;
	int x, y;

	GetXY(&x, &y);
	for (i = 0;i < 10;i++) {
		GotoXY(x0, y0 + i);
		msg[i][0] = 0x00;
		printmsg(msg[i]);
	}
	n = 0;
	GotoXY(x, y);
}
void show_msg(char *msgs)
{

	int x, y;
	int i;
	char * ptr;

	GetXY(&x, &y);
	if (n < 10) {
		strcpy_s(msg[n], 40, msgs);
		GotoXY(x0, y0 + n);
		printmsg( msg[n]);
		n++;
	}
	else {
		ptr = msg[0];
		for (i = 0;i < n;i++) {
			msg[i] = msg[i + 1];
		}

		msg[n-1] = ptr;
		strcpy_s(msg[n-1], 40, msgs);
		for (i = 0;i < n;i++) {
			GotoXY(x0, y0 + i);
			printmsg( msg[i]);
		}
	}
	GotoXY(x,y);
}
void printmsg(char * s) 
{
	int i;
	for (i = 0;s[i] && i < 40;i++) {

		if(s[i]!='\n')putchar(s[i]);
		else putchar(' ');
	}
	for (;i < 40;i++) {
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
void GetXY(int * x, int * y)
{
	// Set the cursor position.
	HANDLE StdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO ScreenBufferInfo = { 0 };
	GetConsoleScreenBufferInfo(StdOut, &ScreenBufferInfo);

	*x = ScreenBufferInfo.dwCursorPosition.X;
	*y = ScreenBufferInfo.dwCursorPosition.Y;

}