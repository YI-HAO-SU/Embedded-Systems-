#ifndef UserMgr_H
#define UserMgr_H
#pragma once

typedef  struct {
	int id;
	char IP[20];
	SOCKET skt;
}Client;

typedef struct {
	char v;//valid flag
	char name[40];
	char IP[20];
	SOCKET skt;
}UserTable;

void initUserTable(void);
int addClientTable(Client * cip);
void writeClientName(int i, char * name);
int listUserTable(char * outBuf);
int sendMsg(int sid, char *dnn, char *msg);
int releaseClient(int id);
#endif //UserMgr_H