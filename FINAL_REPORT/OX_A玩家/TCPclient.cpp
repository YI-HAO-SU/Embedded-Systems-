#include "pch.h"
#include "InputQueue.h"
#include <iostream>
#include <conio.h>
#include <string.h>
#include <process.h>

using namespace std;
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <WINSOCK2.H>
#pragma comment(lib, "wsock32.lib")
#include "ShowMsg.h"
#include "OX.h"

#define			ServerIP					"127.0.0.1"	//port
#define			ServerPort					4100	//port
#define			BUFFERSIZE					100		//每次接受或傳送的緩衝大小
#define			ClientName					"john"
#define         PartnerName					"tom"
WSADATA			WsaData;

SOCKET			ServerSocket;						//Server的socket

void	ExitClient(void);
void	connectServer(void);				//傳送訊息給Server

void DataRecv(void *p);
int OX_complete = 0;
char OXflag = 'O';
extern char turn;

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
	initialInputQ();
	cout << "Connect successfully! You are O" << endl;	
	_beginthread(DataRecv, 1, (void *)buf);
	_beginthread(OX, 1, (void *)buf);
//------------------------------------------傳送給Server訊息------------------------------------------// 		 
	strcpy_s(buf, BUFFERSIZE, "Hello!\n abc 123");
	rVal = send(ServerSocket, buf, BUFFERSIZE, 0);
	Sleep(1000);
	sprintf_s(buf, BUFFERSIZE, "login %s",ClientName);
	rVal = send(ServerSocket, buf, BUFFERSIZE, 0);
	
	while (rVal == BUFFERSIZE && OX_complete==0)
	{
		int pos;

		if(turn==OXflag){
			pos = -1;
			do {
				do {
					if (_kbhit()) {
						gets_s(buf, 100);
						printf("Next X turn\n");
						printf("This turn O press ");
						break;
					}
					Sleep(1);
				} while (OX_complete == 0);	

				if (OX_complete != 0) {
					pos = 0;
					break;
				}

				sscanf_s(buf, "%d", &pos);
				if (pos <= 0 || pos >= 10) {
					printf("Input Error!!!\n>>");
				}
			} while (pos <= 0 );
		
			putClientQ(pos);

			sprintf_s(buf, BUFFERSIZE, "SendTo %s %d", PartnerName,pos);
			rVal = send(ServerSocket, buf, BUFFERSIZE, 0);
		}
		else {
			Sleep(1);
		}

	}

	//------------------------------------------------結束------------------------------------------------//	     																					  //
}					
void DataRecv(void *p)
{
	int rVal;
	char buf[BUFFERSIZE + 1];
	char msg[41], *pt1,*pt2;

	while (rVal = recv(ServerSocket, buf, BUFFERSIZE, 0)) {
		int pos;

		if (rVal <= 0)break;
		buf[rVal] = 0x00;
		sprintf_s(msg, 40, "[from %s]", PartnerName);
		if ((pt1=strstr(buf, msg))!=NULL) {
			pt2 = strstr(pt1, "] ");
			if (pt2 != NULL) {
				sscanf_s((pt2 + 2), "%d", &pos);
				putRemoteQ(pos);
			}
		}
		sprintf_s(msg, 40, "[Server> %s", buf);
		show_msg(msg);
	}
	printf("Exit DataRecv!!!\n");
	_endthread();
}//