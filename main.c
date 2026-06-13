/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: assabich <assabich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/13 21:01:58 by assabich          #+#    #+#             */
/*   Updated: 2026/06/13 21:16:10 by assabich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main ()
{
    //1. create a socket for the client 
    int clientsockFD = socket(AF_INET, SOCK_STREAM, 0);
    if (clientsockFD != -1)
    {
        printf("client Socket ID: %d\n", clientsockFD);
    }
    else
    {
        printf("Failed to create a socket.\n");
        exit(1);
    }

    //2. connect the client to a specific server
    struct sockaddr_in  serverAddress;
    memset(&serverAddress, 0, sizeof(serverAddress));
    
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = inet_addr("127.0.0.1");
    serverAddress.sin_port = htons(1984);
    
    if (connect(clientsockFD, (struct sockaddr)&serverAddress, sizeof(serverAddress)) == 0)
    {
        printf("connected successfulyy.\n");
    }
    else
    {
        printf("Failed to connect.\n");
        exit(1);
    }
    //3. send data to the server
    
    //4. receive data from the server
    
}