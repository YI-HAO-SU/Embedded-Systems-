// TCPServer_s.cpp : 此檔案包含 'main' 函式。程式會於該處開始執行及結束執行。
//

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

	SOCKET	ClientSocket = accept(sck1, (sockaddr FAR*)&addrClient, &addrClientlen);			  //

	int rVal;
	char buf[BUFFERSIZE + 1];

	while ((rVal = recv(ClientSocket, buf, BUFFERSIZE, 0)) > 0) {
		buf[rVal] = 0x00;
		printf("[Client> %s\n", buf);

		if ( (buf[0] == 'c') && (buf[1] == 'm') && (buf[2] == 'd') && (buf[3] == '1') ) {
			strcpy_s(buf, BUFFERSIZE, "Hello!\n");
			rVal = send(ClientSocket, buf, BUFFERSIZE, 0);
		}
		else if ( (buf[0] == 'c') && (buf[1] == 'm') && (buf[2] == 'd') && (buf[3] == '2') ) {
			strcpy_s(buf, BUFFERSIZE, "OK!\n");
			rVal = send(ClientSocket, buf, BUFFERSIZE, 0);
		}
		else {
			strcpy_s(buf, BUFFERSIZE, "Roger!\n");
			rVal = send(ClientSocket, buf, BUFFERSIZE, 0);
		}
	}

	cout << "Server exiting..." << endl;															  //
	closesocket(sck1);																		  //
	closesocket(ClientSocket);																		  //
	WSACleanup();																					  //
																				  //
	system("pause");																				  //
	return 0;																						  //
}																									  //
////////////////////////////////////////////////////////////////////////////////////////////////////////
