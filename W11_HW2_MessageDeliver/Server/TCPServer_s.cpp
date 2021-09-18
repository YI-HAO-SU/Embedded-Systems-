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

#define			ServerPort					4100	//port
#define			BUFFERSIZE					100		//每次接受或傳送的緩衝大小

////////////////////////////////////////////////////////////////////////////////////////////////////////
typedef struct {
	char IP[20];
	SOCKET skt;
}Client;

void DataRecv(void* p);
void GotoXY(SHORT x, SHORT y);
void GetXY(int* x, int* y);
int position = 2;

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
	char buf[BUFFERSIZE + 1];
	Client* cptr;
	//char IP[20];
	//strcpy_s(20, IP,(char*)p);
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

		printf("[%s> %s", cptr->IP, buf);

		if ((buf[0] == 'c') && (buf[1] == 'm') && (buf[2] == 'd') && (buf[3] == '1')) {
			strcpy_s(buf, BUFFERSIZE, "Hello!\n");
		}
		else if ((buf[0] == 'c') && (buf[1] == 'm') && (buf[2] == 'd') && (buf[3] == '2')) {
			strcpy_s(buf, BUFFERSIZE, "OK!\n");
		}
		else {
			strcpy_s(buf, BUFFERSIZE, "Roger!\n");
		}
		
		rVal = send(cptr->skt, buf, BUFFERSIZE, 0);
		GotoXY(a, b);
	}
	printf("Exit DataRecv!!");
	_endthread();
}

// Set current cursor position.
void GotoXY(SHORT x, SHORT y)
{
	// Set the cursor position.
	HANDLE StdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD Cord;						
	Cord.X = x;
	Cord.Y = y;
	SetConsoleCursorPosition(StdOut, Cord);
}

//將指標現在的位置寫入x,y
void GetXY(int* x, int* y) 
{
	// Set the cursor position.
	HANDLE StdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO ScreenBufferInfo = { 0 };
	GetConsoleScreenBufferInfo(StdOut, &ScreenBufferInfo);
	*x = ScreenBufferInfo.dwCursorPosition.X;
	*y = ScreenBufferInfo.dwCursorPosition.Y;
}

//
////////////////////////////////////////////////////////////////////////////////////////////////////////
