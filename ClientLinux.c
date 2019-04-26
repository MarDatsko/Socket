#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>

#define PORT 5555
#define IP "127.0.0.1"

int main(int argc, char const *argv[])
{
    int clientSocket = 0;
    int testSocket = 0;
    struct sockaddr_in client_addr;
    int client_addr_len = sizeof(client_addr);
    char text[1024] = {0};

    // Creating socket file descriptor
    clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket < 0)
    {
        printf("Socket wasn't created\n");
        return 0;
    }

    //Fill zero struct sockaddr_in
    memset(&client_addr, '0', client_addr_len);

    client_addr.sin_family = AF_INET;
    client_addr.sin_port = htons(PORT);

    // Convert IPv4 addresses from text to binary form
    testSocket = inet_pton(AF_INET, IP , &client_addr.sin_addr);
    if (testSocket <= 0)
    {
         printf ( "Error converting address/ Invalid address/ Address not supported \n" );
         return 0;
    }

    //Connection to the server
    testSocket = connect(clientSocket, (struct sockaddr *)&client_addr, client_addr_len);
    if(testSocket < 0)
    {
        printf("No connection to the server\n");
        return 0;
    }
    printf("Conected to server\n");

    //Send massege
    printf("Write massege what do you want send\n");
    gets(text);
    send(clientSocket , text , strlen(text) , 0 );

    return 0;
}
