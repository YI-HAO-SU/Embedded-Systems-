// TCPServer_s.cpp : 此檔案包含 'main' 函式。程式會於該處開始執行及結束執行。
//
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include<stdio.h>
#include<conio.h>
#include <stdlib.h>
#include "pch.h"
#include "ShowMsg.h"
#include "funt.h"
#include "UserMgr.h"
#include <iostream>
#include <process.h>
#include <string.h>
using namespace std;
#include <WINSOCK2.H>
#pragma comment(lib, "wsock32.lib")
#include <TimeAPI.h>
#pragma comment(lib, "Winmm.lib")


#define			ServerPort					4100	//port
#define			BUFFERSIZEChat				100		//每次接受或傳送的緩衝大小

void WaitClient(void * p);
void DataRecv(void *p);

void waitClient_C(void* p);
void DataRecv_C(void* p);
int delNL(char* buf);
int position = 2;
static int LB = 10;

////////////////////////////////////////////////////////////////////////////////////////////////////////
int main(int argc, char* argv[])																	  //
{																									  //
	WSADATA			WsaData;

	SOCKET			sck1;							//自己的socket
	SOCKADDR_IN		sa;							//自己的SOCKADDR_IN結構

	if (0 != WSAStartup(MAKEWORD(1, 1), &WsaData)) {												  //																								
		WSACleanup();																			  //
		exit(0);
	}																								  //
//---------------------------------------------建立SCOKET---------------------------------------------//
	sck1 = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);											  //
	if (INVALID_SOCKET == sck1) {																  //	
		WSACleanup();																			  //
		exit(0);
	}																								  //
//------------------------------------------------BIND------------------------------------------------//
	sa.sin_family = AF_INET;																	  //
	sa.sin_port = htons(ServerPort);															  //
	sa.sin_addr.s_addr = INADDR_ANY;															  //
	if (SOCKET_ERROR == bind(sck1, (LPSOCKADDR)&sa, sizeof(sa))) {					  //
		closesocket(sck1);
		WSACleanup();																			  //
		exit(0);
	}		
//-----------------------------------------------LISTEN-----------------------------------------------// 
	if (SOCKET_ERROR == listen(sck1, 1)) {														  //
		closesocket(sck1);
		WSACleanup();																				  //
		exit(0);
	}										
	
	char c;
	cout << "a: OX game  b: Chat Room  c: Chat Room Server View" << endl;
	c = _getch();
	cout << "You choose " << c;
	if (c == 'a') {
		cout << " OX game" << endl;
	}
	else if (c == 'b') {
		cout << " Chat Room" << endl;
	}
	else if (c == 'c') {
		cout << " Chat Room Server View" << endl;
	}
	else {
		cout << " INPUT ERROR" << endl;
	}

	//cout << "Server succeeded!" << endl;															  //
	//cout << "Waiting for new clients..." << endl;													  //
//-----------------------------------------------送訊息-----------------------------------------------//	

	switch (c)
	{
		case('a'): {																					//OXgame
			cout << "Server succeeded!" << endl;															  //
			cout << "Waiting for new clients..." << endl;
			initUserTable();
			_beginthread(WaitClient, 1, (void*)&sck1);
			break;
		}
		case('b'): {																					//Mulitythread SendTo function
			cout << "Server succeeded!" << endl;															  //
			cout << "Waiting for new clients..." << endl;
			_beginthread(WaitClient, 1, (void*)&sck1);
			break;
		}
		case('c'): {																					//Mulitythread in Server View
			cout << "Server succeeded!" << endl;															  //
			cout << "Waiting for new clients..." << endl;
			_beginthread(waitClient_C, 1, (void*)&sck1);
			break;
		}
		default: {
			cout << "Server exiting..." << endl;															  //
			closesocket(sck1);																		  //																		  //
			WSACleanup();																					  //																			  //
			system("pause");																				  //
			return 0;
			break;
		}
	}
	while (1) {
		Sleep(1000);
	}
	cout << "Server exiting..." << endl;															  //
	closesocket(sck1);																		  //																		  //
	WSACleanup();																					  //																			  //
	system("pause");																				  //
	return 0;																						  //
}	

//OX & Mulitythread SendTo function
void WaitClient(void * p)
{
	sockaddr_in addrClient;
	int addrClientlen = sizeof(addrClient);

	Client cip;
	cip.skt = accept(*((SOCKET *)p), (sockaddr FAR*)&addrClient, &addrClientlen);			  //
	
	_beginthread(WaitClient, 1, p);	
	strcpy_s(cip.IP, 20, inet_ntoa(addrClient.sin_addr));

	cip.id = addClientTable(&cip);

	int rVal;
	char buf[BUFFERSIZE + 1];

	initShowMsg(40,1);
	_beginthread(DataRecv, 1, (void *)&cip);
	while (1) {
		printf("[%s>> ", cip.IP);
		scanf_s("%s", buf, 100);
		rVal = send(cip.skt, buf, BUFFERSIZE, 0);
	}
	releaseClient(cip.id);
	printf("Client[%s] exiting...", cip.IP);															  //
																		  //
	closesocket(cip.skt);																		  //																						  //
}	
void DataRecv(void *p)
{
	int rVal;
	msgBuf mbuf;
	char msg[41];
	Client * cptr;

	cptr = (Client *)p;
	mbuf.id = cptr->id;
	while (rVal = recv(cptr->skt, mbuf.buf, BUFFERSIZE, 0)) {
		if (rVal <= 0)break;

		mbuf.buf[rVal] = 0x00;
		sprintf_s(msg, 40, "[%s> %s", cptr->IP, mbuf.buf);
		show_msg(msg);
		
//		strcpy_s(buf, BUFFERSIZE, msg);
		if(cmdInterpreter(&mbuf))
		    rVal = send(cptr->skt, mbuf.buf, BUFFERSIZE, 0);
		else {
			strcpy_s(mbuf.buf, BUFFERSIZE, "Command Error!!");
			rVal = send(cptr->skt, mbuf.buf, BUFFERSIZE, 0);
		}

	}
	printf("Exit Server DataRecv!!!\n");
	_endthread();
}//

////////////////////////////////////////////////////////////////////////////////////////////////////////
//Mulitythread in Server View
static int clientN = 0;
void waitClient_C(void* p) {
	sockaddr_in addrClient;
	int addrClientlen = sizeof(addrClient);
	Client cip;
	cip.skt = accept(*(SOCKET*)p, (sockaddr FAR*) & addrClient, &addrClientlen);			  //
	cip.id = clientN;
	clientN++;
	_beginthread(waitClient_C, 1, p);

	strcpy_s(cip.IP, 20, inet_ntoa(addrClient.sin_addr));

	int rVal;
	char buf[BUFFERSIZEChat + 1];

	initShowMsg_C(cip.id, 40, 1 + cip.id * 10, 10);
	_beginthread(DataRecv_C, 1, (void*)&cip);

	while (1) {
		printf("[%s>>", cip.IP);
		//		scanf_s("%s", buf, 100);
		gets_s(buf, 99);
		delNL(buf);
		rVal = send(cip.skt, buf, BUFFERSIZEChat, 0);
		++position;
	}

	printf("Client[%s] exiting...", cip.IP);													  //
																				  //
	closesocket(cip.skt);																			  //
}
void DataRecv_C(void* p)
{
	int rVal;
	char buf[BUFFERSIZEChat + 1], msg[41];
	Client* cptr;
	//char IP[20];

	cptr = (Client*)p;
	int i = 1;
	int a, b;

	while (rVal = recv(cptr->skt, buf, BUFFERSIZEChat, 0)) {
		GetXY(&a, &b);
		GotoXY(65, ++i);

		if (rVal <= 0) {
			break;
		}
		buf[rVal] = 0x00;

		sprintf_s(msg, 40, "[%s> %s", cptr->IP, buf);
		show_msg_C(cptr->id, msg, 10);

		//strcpy_s(buf, BUFFERSIZE, msg);
		if (cmdInterpreter_C(cptr->id, buf)) {
			rVal = send(cptr->skt, buf, BUFFERSIZEChat, 0);
		}
		else {
			//strcpy_s(buf, BUFFERSIZEChat, "Command Error!");
			rVal = send(cptr->skt, buf, BUFFERSIZEChat, 0);
		}
		GotoXY(a, b);
	}
	printf("Exit Server DataRecv!!");
	_endthread();
}
int delNL(char* buf) {
	int i;
	for (i = 0; buf[i]; i++)
	{
		if (buf[i] == '\n') {
			buf[i] = 0x00;
			break;
		}
	}
	return i;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////
