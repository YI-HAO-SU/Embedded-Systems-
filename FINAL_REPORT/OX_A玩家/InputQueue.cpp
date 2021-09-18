#include "pch.h"
#include "InputQueue.h"
#include <iostream>
static CQueue clientQ, remoteQ;
int isFull(CQueue * p);
int isEmpty(CQueue * p);
void initialInputQ(void)
{
	clientQ.front = clientQ.tail = 0;
	remoteQ.front = remoteQ.tail = 0;
}
int insertQ(CQueue * p, int pos)
{
	if (!isFull(p)) {
		p->data[p->front] = pos;
		p->front = (p->front + 1) & 0x0F;
		return pos;
	}
	return -1;
}
int deleteQ(CQueue * p)
{
	int pos;

	if (!isEmpty(p)) {
		pos=p->data[p->tail];
		p->tail = (p->tail + 1) & 0x0F;
		return pos;
	}
	return -1;
}
int isEmpty(CQueue * p)
{
	if (p->tail == p->front)return 1;
	return 0;
}
int isFull(CQueue * p)
{
	if (p->tail == ((p->front+1)&0x0F))return 1;
	return 0;
}
//=====================================
int putClientQ(int pos)
{
	return insertQ(&clientQ, pos);
}
int getClientQ(void)
{
	return deleteQ(&clientQ);
}
int putRemoteQ(int pos)
{
	return insertQ(&remoteQ, pos);
}
int getRemoteQ(void)
{
	return deleteQ(&remoteQ);
}