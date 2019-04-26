#include <Ws2tcpip.h>
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <WinSock2.h>

#pragma comment(lib,"ws2_32.lib")
#pragma warning(disable: 4996)
#define PORT 5555
#define IP "127.0.0.1"



int main(int argc, char const *argv[])
{
	//Download library for 'winSock2'
	WSAData wsa;
	WORD dll = MAKEWORD(2, 1);
	if (WSAStartup(dll, &wsa) != 0)
	{
		printf(" Error\n ");
	}

	SOCKET serverSocket;
	char buffer[1024] = { 0 };
	SOCKADDR_IN server_addr;
	SOCKET clientSocket;
	int server_addr_len = sizeof(server_addr);

	// Creating socket file descriptor
	if ((serverSocket = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		printf("Error socket doesn't create \n");
		return 0;
	}

	inet_pton(AF_INET, IP, &server_addr.sin_addr);
	server_addr.sin_port = htons(PORT);
	server_addr.sin_family = AF_INET;

	//Connect address with socket
	if (bind(serverSocket, (struct sockaddr*)&server_addr, server_addr_len) < 0)
	{
		printf("Error bind \n");
		return 0;
	}

	//Socket waits for the client to approach the server to make a connection
	if (listen(serverSocket, 5) < 0)
	{
		printf("Error listen\n ");
		return 0;
	}

	//Connect client to the server
	if ((clientSocket = accept(serverSocket, (struct sockaddr*)&server_addr, &server_addr_len)) < 0)
	{
		printf("Error accept \n");
		return 0;
	}
	else
	{
		printf("Client connected\n ");
	}

	//Read the text sent by the client
	recv(clientSocket, buffer, sizeof(buffer),NULL);
	printf("%s\n", buffer);

	system("pause");
	return 0;

}