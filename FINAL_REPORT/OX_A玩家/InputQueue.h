#pragma once
typedef struct {
	int data[16];
	char front, tail;
}CQueue;
void initialInputQ(void);
int putClientQ(int pos);
int getClientQ(void);
int putRemoteQ(int pos);
int getRemoteQ(void);
