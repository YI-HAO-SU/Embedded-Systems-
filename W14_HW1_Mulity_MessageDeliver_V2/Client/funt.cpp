// funt.cpp : 定義主控台應用程式的進入點。
//

#include "pch.h"
#include <stdio.h>
#include <windows.h>
#include "funt.h"
#include "ShowMsg.h"
static void login(void *p);
static void hello(void *p);
static void goodbye(void *p);
static void cls(void *p);
static void EXIT(void *p);

typedef struct{
	const char * cmdname;
	void (*f)(void *);
}CmdTBL;

static CmdTBL CT[] = { {"CMD1",hello},
				{"CMD2",goodbye},
	            {"cls",cls},
				{"EXIT",EXIT},
				{"Hello!\n",login},
				{NULL,NULL}
				} ;

void login(void *p)
{
	char * s;
	char buf[100];
	s = (char *)p;
	sprintf_s(buf,100,"Welcome[%s] \n",s);
	strcpy_s(s,100, buf);
}
void hello(void *p)
{
	char * s;
	char buf[100];
	s = (char *)p;
	sprintf_s(buf, 100, "hello[%s] \n", s);
	strcpy_s(s, 100, buf);
}

void goodbye(void *p)
{
	char * s;
	char buf[100];
	s = (char *)p;
	sprintf_s(buf, 100, "goodbye[%s] \n", s);
	strcpy_s(s, 100, buf);
}
void cls(void *p)
{
	char * s;
	char buf[100];
	s = (char *)p;
	sprintf_s(buf, 100, "OK!! \n", s);
	strcpy_s(s, 100, buf);
	ClrMsg();
}
void EXIT(void *p)
{
	exit(0);
}

int cmdInterpreter(char * cmd)
{
	int i,k;
	char c = 0x00;
	for (i = 0;cmd[i] && cmd[i] != ' ';i++);
	if (cmd[i] == ' ') {
		c = ' ';cmd[i] = 0x00;
	}

	for (k = 0;CT[k].cmdname != NULL;k++) {
		if (!strcmp(cmd, CT[k].cmdname)) {
			cmd[i] = c;
			CT[k].f(cmd);
			return 1;
		}

	} 
	return 0;
}
