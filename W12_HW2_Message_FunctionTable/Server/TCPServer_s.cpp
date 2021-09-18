// TCPServer_s.cpp : 此檔案包含 'main' 函式。程式會於該處開始執行及結束執行。
//
#pragma warning(disable:4996)

#include "pch.h"
#include <iostream>
#include <process.h>
#include <string.h>
using namespace std;
#include <WINSOCK2.H>
#pragma comment(lib, "wsock32.lib")
#include <TimeAPI.h>
#pragma comment(lib, "Winmm.lib")
#include "ShowMessage.h"
#include "funt.h"

#define			ServerPort					4100	//port
#define			BUFFERSIZE					100		//每次接受或傳送的緩衝大小

////////////////////////////////////////////////////////////////////////////////////////////////////////
typedef struct {
	char IP[20];
	SOCKET skt;
}Client;

void DataRecv(void* p);
int position = 2;
static int LB = 10;

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
	}																								  //
//-----------------------------------------------LISTEN-----------------------------------------------// 
	if (SOCKET_ERROR == listen(sck1, 1)) {														  //
		closesocket(sck1);
		WSACleanup();																				  //
		exit(0);
	}																								  //
	cout << "Server succeeded!" << endl;															  //
	cout << "Waiting for new clients..." << endl;													  //
//-----------------------------------------------送訊息-----------------------------------------------//	
	sockaddr_in addrClient;
	int addrClientlen = sizeof(addrClient);

	Client cip;
	cip.skt = accept(sck1, (sockaddr FAR*)&addrClient, &addrClientlen);			  //
	strcpy_s(cip.IP, 20, inet_ntoa(addrClient.sin_addr));

	int rVal;
	char buf[BUFFERSIZE + 1];

	initShowMsg(40, 1, 10);
	_beginthread(DataRecv, 1, (void*)&cip);

	while (1) {
		printf("[%s>>", cip.IP);
		scanf_s("%s", buf, 100);
		rVal = send(cip.skt, buf, BUFFERSIZE, 0);
		++position;
	}

	cout << "Server exiting..." << endl;													  //
	closesocket(sck1);																				  //
	closesocket(cip.skt);																			  //
	WSACleanup();																					  //
																												  //
	system("pause");																					  //
	return 0;																								  //
}

void DataRecv(void* p)
{
	int rVal;
	char buf[BUFFERSIZE + 1],msg[41];
	Client* cptr;
	//char IP[20];

	cptr = (Client*)p;
	int i = 1;
	int a, b;

	while (rVal = recv(cptr->skt, buf, BUFFERSIZE, 0)) {
		GetXY(&a, &b);
		GotoXY(65, ++i);

		if (rVal <= 0) {
			break;
		}
		buf[rVal] = 0x00;

		sprintf_s(msg,40,"[%s> %s", cptr->IP, buf);
		show_msg(msg,10);

		//strcpy_s(buf, BUFFERSIZE, msg);
		if (cmdInterpreter(buf)) {
			rVal = send(cptr->skt, buf, BUFFERSIZE, 0);
		}
		else {
			strcpy_s(buf, BUFFERSIZE, "Command Error!");
			rVal = send(cptr->skt, buf, BUFFERSIZE, 0);
		}
		GotoXY(a, b);
	}
	printf("Exit Server DataRecv!!");
	_endthread();
}
//
////////////////////////////////////////////////////////////////////////////////////////////////////////
