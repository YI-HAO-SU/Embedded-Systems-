#include "pch.h"
#include <stdio.h>
#include <string.h>
#include "UserMgr.h"
static UserTable UT[10];
void initUserTable(void)
{
	int i;
	for (i = 0;i < 10;i++) {
		UT[i].v = 0;
		UT[i].name[0] = 0x00;
	}
}
int getAvalableUT(void)
{
	int i;
	for (i = 0;i < 10;i++)
		if (UT[i].v == 0)return i;
	return -1;
}
int getUTidByName(char * name)
{
	int i;
	for (i = 0;i < 10;i++) {
		if (UT[i].v) {
			if (strcmp(UT[i].name, name) == 0)return i;
		}
	}
	return -1;
}
int releaseClient(int id)
{
	UT[id].v = 0;
	UT[id].name[0] = 0x00;
	return 1;
}
int addClientTable(Client * cip)
{
	int i;
	i = getAvalableUT();
	if (i >= 0) {
		strcpy_s(UT[i].IP, 20, cip->IP);
		UT[i].skt = cip->skt;
		UT[i].v = 1;
	}
	
	return i;
}
void writeClientName(int id, char * name)
{
	strcpy_s(UT[id].name, 40, name);
}
int listUserTable(char * outBuf)
{
	int i,n=0;
	int k = 0;
	for (i = 0;i < 10;i++) {
		if (UT[i].v) {
			if (UT[i].name[0] != 0x00) {
				sprintf_s(&outBuf[k], 40, "%s|", UT[i].name);
				k = strlen(outBuf);
				n++;
			}
		}
	}
	return n;
}
int sendMsg(int sid, char *dnn, char *msg)
{
	int did,rVal=0;
	char buf[100];

	did = getUTidByName(dnn);
	if (did >= 0) {
		sprintf_s(buf, 100, "[from %s] %s", UT[sid].name, msg);
		rVal = send(UT[did].skt, buf, BUFFERSIZE, 0);
	}
	return rVal;
}