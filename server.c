/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: assabich <assabich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/14 15:53:07 by assabich          #+#    #+#             */
/*   Updated: 2026/06/14 17:35:41 by assabich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main()
{
    //1. create a socket for a server 
    
    int serversocketFD = socket(AF_INET, SOCK_STREAM, 0);
    if (serversocketFD != -1)
    {
        printf("Server Scoket ID: %d\n", serversocketFD);
    }
    else
    {
        printf("Failed to create a socket.\n");
        exit(1);
    }
    
    //2. bind this socket to a specific port number
    struct sockaddr_in serverAddress;
    memset(&serverAddress, 0, sizeof(serverAddress));
    
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = htonl(INADDR_ANY);
    serverAddress.sin_port = htons(4444);
    
    if (bind(serversocketFD, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) == 0)
    {
        printf ("Server is binded to port no.4444\n");
    }
    else
    {
        printf("Failed to bind\n");
        exit (1);
    }
    
    //3. listen to the clients connection requests
    if (listen (serversocketFD, 1) == 0)
    {
        printf("listening ...\n");
    }
    else
    {
        printf("Failed to listen.\n");
        exit (1);
    }
    
    //4. accept connection request
    struct sockaddr_in connectedclientAddress;
    memset(&connectedclientAddress, 0, sizeof(connectedclientAddress));
    
    connectedclientAddress.sin_family = AF_INET;
    connectedclientAddress.sin_addr.s_addr = htonl(INADDR_ANY);
    connectedclientAddress.sin_port = htons(4444);
    
    int clientAddrLength = 0;
    int connectserversockFD = accept(serversocketFD, (struct sockaddr*)&connectedclientAddress, &clientAddrLength);
    if (connectserversockFD == -1)
    {
        printf("Failed to accept a connection request\n");
    }
    else 
    {
        printf("Accepted a request at socket ID: %d\n", connectserversockFD);
    }
    
    //5. send or receive data from the client
    char receivedMsg[1024];
    memset(receivedMsg, 0, sizeof(receivedMsg));
    
    recv(connectserversockFD, receivedMsg, 1024, 0);
    printf ("received message: %s\n", receivedMsg);
    
    //7.send to client
    char buffer[1024] = "Hi ! I am Weressa\n";
    send (connectserversockFD, buffer, strlen(buffer), 0);

    //6. close the socket
    close(serversocketFD);
    close (connectserversockFD);
    
    return (0);
}
