#pragma once
typedef struct {
	int id;
	char buf[1024];
}msgBuf;
int cmdInterpreter(msgBuf * cmd);
int cmdInterpreter_C(int id, char* cmds);
