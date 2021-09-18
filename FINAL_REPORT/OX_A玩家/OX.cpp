// OX2.cpp : 此檔案包含 'main' 函式。程式會於該處開始執行及結束執行。
//

#include "pch.h"
#include "ShowMsg.h"
#include "InputQueue.h"
#include "OX.h"
#include <stdio.h>
#include <iostream>
void print_form(void);
int sb_check(char turn);
extern int OX_complete;
char sb[3][3] = { 0x20, 0x20, 0x20,
				  0x20, 0x20, 0x20,
				  0x20, 0x20, 0x20 };
char turn = 'O';
extern char OXflag;
void OX(void *p1)
{
	
	int pos,n=0;
	char *p;

	p = (char *)sb;

	print_form();
	do {
		printf("[%c]>>", turn);
//		scanf_s("%d", &pos);
		if (turn == OXflag) {
			while ((pos = getClientQ()) <= 0) {
				Sleep(1);
			}
		}
		else {
			while ((pos = getRemoteQ()) <= 0) {
				Sleep(1);
			}			
		}
		printf("%d\n", pos);
		p[pos - 1] = turn;
		print_form();
		if (sb_check(turn)) {
			printf("Winner is [%c]!!!\n", turn);
			break;
		}
		turn = (turn == 'O') ? 'X' : 'O';
		n++;
	} while (n < 9);
	if (n == 9) {
		printf("The competition is draw!!!\n");
	}
	OX_complete = 1;
}
int sb_check(char turn)
{
	int i;
	for (i = 0;i < 3;i++)
	{
		if (sb[i][0] == sb[i][1] && sb[i][1] == sb[i][2]&& sb[i][0]==turn)return 1;
	}	
	for (i = 0;i < 3;i++)
	{
		if (sb[0][i] == sb[1][i] && sb[1][i] == sb[2][i]&&sb[0][i] == turn)return 1;
	}
	if (sb[0][0] == sb[1][1] && sb[1][1] == sb[2][2] && sb[0][0] == turn)return 1;
	if (sb[2][0] == sb[1][1] && sb[1][1] == sb[0][2] && sb[0][2] == turn)return 1;
	return 0;
}
void print_form(void)
{
	char *p;
	const char * frm[] = {
		" %c  | %c  | %c  \n",
		"----+----+----\n",
		" %c  | %c  | %c  \n",
		"----+----+----\n",
		" %c  | %c  | %c  \n" };
	int i, k = 0;
	int x, y;

	p = (char *)sb;
	GetXY(&x, &y);

	for (i = 0;i < 5;i++) {
		GotoXY(20, i+1);
		if (!(i % 2)) {
			printf(frm[i],	((p[k]==0x20)? '0'+k+1:p[k]),
							((p[k+1] == 0x20) ? '0' + k + 2 : p[k+1]),
							((p[k+2] == 0x20) ? '0' + k + 3 : p[k+2]));
			k += 3;
		}
		else {
			printf(frm[i]);
		}
	}
	GotoXY(x, y);
}

