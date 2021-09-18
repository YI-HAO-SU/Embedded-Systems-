#include "pch.h"
#include <iostream>
#include <string.h>
#include <process.h>

using namespace std;

#include <WINSOCK2.H>
#pragma comment(lib, "wsock32.lib")
#include "ShowMessage.h"
#include "OX.h"

#define			ServerIP					"127.0.0.1"	//port
#define			ServerPort					4100		//port
#define			BUFFERSIZE					100		//每次接受或傳送的緩衝大小

WSADATA			WsaData;
SOCKET			ServerSocket;							//Server的socket

void	ExitClient(void);
void	connectServer(void);								//傳送訊息給Server
void DataRecv(void* p);

static int LB = 7;												//define reorganization row

//char ServerIP[20];
////////////////////////////////////////////////////////////////////////////////////////////////////////
int main(int argc, char* argv[])																	  //
{																													  //
//-----------------------------------------------初始化-----------------------------------------------//
	if (0 != WSAStartup(MAKEWORD(1, 1), &WsaData)) {					  //																								
		ExitClient();																						  //
	}																												  //

	connectServer();																						  //
//------------------------------------------------結束------------------------------------------------//
	ExitClient();																							  //
	system("pause");																						  //
	return 0;																									  //
}																													  //
////////////////////////////////////////////////////////////////////////////////////////////////////////

void	ExitClient(void)																						  //
{																												//
	cout << "Client exiting..." << endl;														 	  //
	closesocket(ServerSocket);																		  //																		  //
	WSACleanup();																					  //																				  //
}
void	connectServer(void)																			  // 
{

	int rVal;//
	char buf[BUFFERSIZE + 1];
	struct sockaddr_in serveraddr;

	//-----------------------------------------建立Server的SCOKET-----------------------------------------//
	ServerSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);							  //
	if (INVALID_SOCKET == ServerSocket) {																		  //																											 
		ExitClient();																													  //
	}																																			  //
//-----------------------------------------------CONNECT----------------------------------------------//			
	/*
	printf("Enter the connecting address IP :\n>>");
	scanf_s("%s", ServerIP, 20);
	*/
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_addr.s_addr = inet_addr(ServerIP);
	serveraddr.sin_port = htons((unsigned short)ServerPort);
	//
	if (SOCKET_ERROR == connect(ServerSocket, (LPSOCKADDR)&serveraddr, sizeof(serveraddr))) {
		printf("error!");																						//																										
		ExitClient();																							//
	}
	initShowMsg(40, 1, LB);
	cout << "Connect successfully!" << endl;													//

	_beginthread(DataRecv, 1, (void*)buf);
//------------------------------------------傳送給Server訊息------------------------------------------// 		 
	strcpy_s(buf, BUFFERSIZE, "Hello!\n");
	rVal = send(ServerSocket, buf, BUFFERSIZE, 0);
	while (rVal == BUFFERSIZE)
	{
		/*
		rVal = recv(ServerSocket, buf, BUFFERSIZE, 0);
		buf[rVal] = 0x00;
		if (rVal > 0) {
			printf("[Server> %s", buf);
		*/
		OX();
			
		printf(">>");
		scanf_s("%s", buf,100);
		rVal = send(ServerSocket, buf, BUFFERSIZE, 0);
	}

	//------------------------------------------------結束------------------------------------------------//	     																					  //
}																									  //
void DataRecv(void* p) {
	int rval;
	char buf[BUFFERSIZE + 1];
	char msg[41];

	while (rval = recv(ServerSocket, buf, BUFFERSIZE, 0)) {
		if (rval <= 0) {
			break;
		}
		buf[rval] = 0x00;
		sprintf_s(msg,40,"[Server> %s\n", buf);
		show_msg(msg,LB);
	}
	printf("Exit Client DataRecv!!!");
	_endthread();
}