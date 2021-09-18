#include "pch.h"
#include <iostream>
#include <string.h>
#include <process.h>

using namespace std;
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <WINSOCK2.H>
#pragma comment(lib, "wsock32.lib")
#include "ShowMsg.h"

#define			ServerIP					"127.0.0.1"	//port
#define			ServerPort					4100	//port
#define			BUFFERSIZE					100		//每次接受或傳送的緩衝大小

WSADATA			WsaData;

SOCKET			ServerSocket;						//Server的socket

void	ExitClient(void);
void	connectServer(void);				//傳送訊息給Server

void DataRecv(void *p);
////////////////////////////////////////////////////////////////////////////////////////////////////////
int main(int argc, char* argv[])																	  //
{																									  //
//-----------------------------------------------初始化-----------------------------------------------//
	if (0 != WSAStartup(MAKEWORD(1, 1), &WsaData)) {												  //																								
		ExitClient();																				  //
	}																								  //

	connectServer();																				  //
//------------------------------------------------結束------------------------------------------------//
	ExitClient();																					  //
	system("pause");																				  //
	return 0;																						  //
}																									  //
////////////////////////////////////////////////////////////////////////////////////////////////////////

void	ExitClient(void)																				  //
{																									  //
	cout << "Client exiting..." << endl;															  //
	closesocket(ServerSocket);																		  //																		  //
	WSACleanup();																					  //																				  //
}
void	connectServer(void)																			  // 
{

	int rVal;//
	char buf[BUFFERSIZE + 1];
	struct sockaddr_in serveraddr;

	//-----------------------------------------建立Server的SCOKET-----------------------------------------//
	ServerSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);                                         //
	if (INVALID_SOCKET == ServerSocket) {																  //																											 
		ExitClient();																				  //
	}																								  //
//-----------------------------------------------CONNECT----------------------------------------------//			

	serveraddr.sin_family = AF_INET;
	serveraddr.sin_addr.s_addr = inet_addr(ServerIP);
	serveraddr.sin_port = htons((unsigned short)ServerPort);
	//
	if (SOCKET_ERROR == connect(ServerSocket, (LPSOCKADDR)&serveraddr, sizeof(serveraddr))) {
		printf("error!");//																										
		ExitClient();																				  //
	}
	initShowMsg(40, 1);
	cout << "Connect successfully!" << endl;															  //
	_beginthread(DataRecv, 1, (void *)buf);
//------------------------------------------傳送給Server訊息------------------------------------------// 		 
	strcpy_s(buf, BUFFERSIZE, "Hello!\n abc 123");
	rVal = send(ServerSocket, buf, BUFFERSIZE, 0);
	while (rVal == BUFFERSIZE)
	{
//		rVal = recv(ServerSocket, buf, BUFFERSIZE, 0);		
//		if (rVal > 0) {
//			buf[rVal] = 0x00;
//			printf("[Server> %s", buf);
		printf(">> ");
		gets_s(buf,100);
		for (int i = 0;buf[i];i++)
			if (buf[i] == '\n')buf[i] = 0x00;

		rVal = send(ServerSocket, buf, BUFFERSIZE, 0);
//		}

	}

	//------------------------------------------------結束------------------------------------------------//	     																					  //
}					
void DataRecv(void *p)
{
	int rVal;
	char buf[BUFFERSIZE + 1];
	char msg[41];

	while (rVal = recv(ServerSocket, buf, BUFFERSIZE, 0)) {
		if (rVal <= 0)break;
		buf[rVal] = 0x00;
		sprintf_s(msg, 40, "[Server> %s", buf);
		show_msg(msg);
	}
	printf("Exit DataRecv!!!\n");
	_endthread();
}//