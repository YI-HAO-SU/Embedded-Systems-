// funt.cpp : 定義主控台應用程式的進入點。
//

#include "pch.h"
#include <stdio.h>
#include <windows.h>
#include "funt.h"
#include "ShowMessage.h"
static void login(void *p);
static void hello(void *p);
static void goodbye(void *p);
static void cls(void *p);
static void EXIT(void *p);
static int LB = 10;

typedef struct{
	const char * cmdname;
	void (*f)(void *);
}CmdTBL;

typedef struct {
	char* buf;
	int id;
}Cmd;

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
	Cmd* cmd;
	cmd = (Cmd *)p;
	s = cmd->buf;
	sprintf_s(buf,100,"Welcome[%s] \n",s);
	strcpy_s(s,100, buf);
}
void hello(void *p)
{
	char * s;
	char buf[100];
	Cmd* cmd;
	cmd = (Cmd*)p;
	s = cmd->buf;
	sprintf_s(buf, 100, "hello[%s] \n", s);
	strcpy_s(s, 100, buf);
}

void goodbye(void *p)
{
	char * s;
	char buf[100];
	Cmd* cmd;
	cmd = (Cmd*)p;
	s = cmd->buf;
	sprintf_s(buf, 100, "goodbye[%s] \n", s);
	strcpy_s(s, 100, buf);
}
void cls(void *p)
{
	char * s;
	char buf[100];
	Cmd* cmd;
	cmd = (Cmd*)p;
	s = cmd->buf;
	sprintf_s(buf, 100, "cls[%s]!! \n", s);
	strcpy_s(s, 100, buf);
	ClrMsg(cmd->id,LB);
}
void EXIT(void *p)
{
	exit(0);
}

int cmdInterpreter(int id ,char * cmds)
{
	int i=0,k;
	char c = 0x00;
	Cmd cmd;
	for (i = 0; cmds[i] && cmds[i] != ' '; i++) {
		if (cmds[i] == ' ') {
			c = ' ';
			cmds[i] = 0x00;
		}
	}
	
	for (k = 0;CT[k].cmdname != NULL;k++) {
		if (!strcmp(cmds, CT[k].cmdname)) {
			cmds[i] = c;

			cmd.buf = cmds;
			cmd.id = id;
			CT[k].f(&cmd);
			return 1;
		}

	} 
	return 0;
}
