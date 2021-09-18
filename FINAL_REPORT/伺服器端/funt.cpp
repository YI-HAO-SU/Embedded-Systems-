// funt.cpp : 定義主控台應用程式的進入點。
//
#include "pch.h"
#include <stdio.h>
#include <windows.h>
#include "funt.h"
#include "ShowMsg.h"
#include "UserMgr.h"
static void Start(void *p);
static void login(void *p);
static void hello(void *p);
static void goodbye(void *p);
static void cls(void *p);
static void EXIT(void *p);
static void SendTo(void *p);
static void loopback(void *p);

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
				{"login",login},
				{"EXIT",EXIT},
				{"Hello!\n",Start},
				{"SendTo",SendTo},
				{"loopback",loopback},
				{NULL,NULL}
				} ;

void SendTo(void *p)//SendTo tom Hello!!
{
	msgBuf * s;
	char  buf[100], name[40],*ptr1, *ptr2;
	int rVal=0;
	s = (msgBuf *)p;
	ptr1 = strstr(s->buf, " ");
	if (ptr1 != NULL) {
		while (*ptr1 == ' ')ptr1++;
		ptr2 = strstr(ptr1, " ");
		*ptr2 = 0x00;
		rVal=sendMsg(s->id, ptr1, ptr2 + 1);
		if (rVal > 0) {
			sprintf_s(buf, 100, "<SendTo> OK!");
			strcpy_s(s->buf, 100, buf);
		}
		else {
			sprintf_s(buf, 100, "<SendTo> Destination Miss!");
			strcpy_s(s->buf, 100, buf);
		}
	}
	else {
		sprintf_s(buf, 100, "<SendTo> Error! \n");
		strcpy_s(s->buf, 100, buf);
	}
}
void login(void *p)
{
	msgBuf * s;
	char  buf[100],*ptr;
	s = (msgBuf *)p;
	ptr = strstr(s->buf, " ");
	if (ptr != NULL) {
		while (*ptr && *ptr == ' ' )ptr++;
		if (*ptr) {
			writeClientName(s->id, ptr);
			sprintf_s(buf, 100, "Welcome[%s] \n", ptr);
			strcpy_s(s->buf, 100, buf);
		}
		else {
			sprintf_s(buf, 100, "Login Error [Empty User Name]!!");
			strcpy_s(s->buf, 100, buf);
		}
	}
	else {
		sprintf_s(buf, 100, "Login Error!!");
		strcpy_s(s->buf, 100, buf);
	}
}
void Start(void *p)
{
	msgBuf * s;
	char  buf[100];
	s = (msgBuf *)p;
	sprintf_s(buf, 100, "Connect Success!! \n");
	strcpy_s(s->buf, 100, buf);
}
void hello(void *p)
{
	msgBuf * s;
	char buf[100];
	s = (msgBuf *)p;
	sprintf_s(buf, 100, "hello[%s] \n", s->buf);
	strcpy_s(s->buf, 100, buf);
}
void goodbye(void *p)
{
	msgBuf * s;
	char buf[100];
	s = (msgBuf *)p;
	sprintf_s(buf, 100, "goodbye[%s] \n", s->buf);
	strcpy_s(s->buf, 100, buf);
}
void cls(void *p)
{
	msgBuf * s;
	char buf[100];
	s = (msgBuf *)p;
	sprintf_s(buf, 100, "OK!! \n");
	strcpy_s(s->buf, 100, buf);
	ClrMsg();
}
void loopback(void *p)
{
	msgBuf * s;
	char buf[100], *ptr;
	s = (msgBuf *)p;
	ptr = strstr(s->buf, " ");
	sprintf_s(buf, 100, "loopback %s", (ptr+1));
	strcpy_s(s->buf, 100, buf);
}
void EXIT(void *p)
{
	exit(0);
}
int cmdInterpreter(msgBuf * cmd)
{
	int k;
	char c = 0x00,*ptr;

	ptr = strstr(cmd->buf, " ");
	if(ptr != NULL)*ptr = 0x00;

	for (k = 0;CT[k].cmdname != NULL;k++) {
		if (strcmp(cmd->buf, CT[k].cmdname)==0) {
			if (ptr != NULL)*ptr = ' ';
			CT[k].f(cmd);
			return 1;
		}
	} 
	return 0;
}

//Chat
void loginC(void* p)
{
	char* s;
	char buf[100];
	Cmd* cmd;
	cmd = (Cmd*)p;
	s = cmd->buf;
	sprintf_s(buf, 100, "Welcome[%s] \n", s);
	strcpy_s(s, 100, buf);
}
void helloC(void* p)
{
	char* s;
	char buf[100];
	Cmd* cmd;
	cmd = (Cmd*)p;
	s = cmd->buf;
	sprintf_s(buf, 100, "hello[%s] \n", s);
	strcpy_s(s, 100, buf);
}

void goodbyeC(void* p)
{
	char* s;
	char buf[100];
	Cmd* cmd;
	cmd = (Cmd*)p;
	s = cmd->buf;
	sprintf_s(buf, 100, "goodbye[%s] \n", s);
	strcpy_s(s, 100, buf);
}
void clsC(void* p)
{
	char* s;
	char buf[100];
	Cmd* cmd;
	cmd = (Cmd*)p;
	s = cmd->buf;
	sprintf_s(buf, 100, "cls[%s]!! \n", s);
	strcpy_s(s, 100, buf);
	ClrMsg_C(cmd->id, LB);
}

int cmdInterpreter_C(int id, char* cmds)
{
	int i = 0, k;
	char c = 0x00;
	Cmd cmd;
	for (i = 0; cmds[i] && cmds[i] != ' '; i++) {
		if (cmds[i] == ' ') {
			c = ' ';
			cmds[i] = 0x00;
		}
	}

	for (k = 0; CT[k].cmdname != NULL; k++) {
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

