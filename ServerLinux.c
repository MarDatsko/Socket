#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>

#define PORT 5555

int main(int argc, char const *argv[])
{

    int serverSocket = 0;
    int testSocket = 0;
    struct sockaddr_in server_addr;
    char buffer[1024] = {0};
    int opt = 1;
    int server_addr_len = sizeof(server_addr);

    // Creating socket file descriptor
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket < 0)
    {
        printf("Socket wasn't created\n");
        return 0;
    }

    // Forcefully attaching socket to the port 5555
    if (setsockopt(serverSocket, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,&opt, sizeof(opt)))
    {
        printf("Setsockopt Error\n");
        return 0;
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_port = htons(PORT);

    //Connect address with socket
    testSocket = bind(serverSocket, (struct sockaddr *)&server_addr,server_addr_len);
    if (testSocket < 0)
    {
        printf("Bind Error\n");
        return 0;
    }

    //Socket waits for the client to approach the server to make a connection
    testSocket = listen(serverSocket, 3);
    if(testSocket < 0)
    {
        printf("Listen Error\n");
        return 0;
    }

    //Connect client to the server
    testSocket = accept(serverSocket, (struct sockaddr *)&server_addr,(socklen_t*)&server_addr_len);
    if (testSocket < 0)
    {
        printf("Accept Error\n");
        return 0;
    }
    printf("Client Conected\n");

    //Read the text sent by the client
    read( testSocket , buffer, 1024);
    printf("%s\n",buffer);
    return 0;
}
