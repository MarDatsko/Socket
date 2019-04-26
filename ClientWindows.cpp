#include <Ws2tcpip.h>
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <WinSock2.h>

#pragma comment(lib,"ws2_32.lib")
#pragma warning(disable: 4996)
#define PORT 5555
//#define IP "192.168.195.128"
#define IP "127.0.0.1"

int main()
{	
	//Download library for 'winSock2'
	WSAData wsa;
	WORD dll = MAKEWORD(2, 2);
	if (WSAStartup(dll, &wsa) != 0)
	{
		printf("Error\n ");
	}

	SOCKET clientSock;
	SOCKADDR_IN addr;
	char text[1024] = { 0 };

	// Creating socket file descriptor
	if ((clientSock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		printf("Error socket\n");
		return 0;
	}
	else
	{
		printf_s("Socket  create \n");
	}

	inet_pton(AF_INET, IP , &addr.sin_addr);
	addr.sin_port = htons(PORT);
	addr.sin_family = AF_INET;

	//Connection to the server
	if (connect(clientSock, (struct sockaddr*)&addr, sizeof(addr)) < 0)
	{
		printf("Error connect\n");
	}
	else
	{			
		printf("Connected\n");
	
		//Send massege
		printf("Write massege what do you want send\n");
		fgets(text, sizeof(text), stdin);
		send(clientSock, text, strlen(text), 0);
	}


	system("pause");
	return 0;
}

