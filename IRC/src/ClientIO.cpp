#include "Server.hpp"
#include "Parser.hpp"
#include <iostream>
#include <cerrno>       //errno
#include <cstring>      //std::strerror
#include <sys/socket.h> //recv

void Server::clientIO_error(const std::string &mess, int fd) {
	std::cout << "Error in clientIO.cpp: " << mess
			  << ", closing client fd=" << fd << std::endl;
	clientRemove(fd);
}

void Server::queueMessage(int fd, const std::string &message) {
	Client &client = getClient(fd);
	client._outbuffer.append(message);

	if (client._outbuffer.size() > MAX_OUTBUFFER_SIZE) {
		clientIO_error("_outbuffer Overflow", fd);
		return;
	}

	updatePollEvents(fd);
}

void Server::clientRead(int fd) {
	char buffer[512];
	ssize_t bytesRead = recv(fd, buffer, sizeof(buffer), 0);
	//deconnexion normale  du client
	if (bytesRead == 0) {
		clientRemove(fd);
		return;
	}
	//signal a passer OU erreur recv()
	if (bytesRead == -1) {
		if (errno == EAGAIN || errno == EWOULDBLOCK) {
			return;
		}
		clientIO_error("recv() fail", fd);
		return;
	}
	//clientRead = ecrire dans _inbuffer
	Client &client = getClient(fd);
	client._inbuffer.append(buffer, (size_t)bytesRead);

	if (client._inbuffer.size() > MAX_INBUFFER_SIZE) {
		clientIO_error("_inbuffer overflow", fd);
		return;
	}
	
	Parser	parser;
	Request	request;
	
	while (client._inbuffer.find("\r\n") != std::string::npos)
	{
		if (!parser.parseCommand(client, request))
			continue;
		if (request._type != INVALID) {

			handleCommand(fd, request);
			
			/*std::cout << "TYPE: " << request._tokens[0]
						<< std::endl;
			std::cout << "trailing: " << request.trailing
					  << std::endl;*/
		}
	}
}

void Server::clientWrite(int fd) {
	Client &client = getClient(fd);
	//finalement rien a ecrire
	if (client._outbuffer.empty()) {
		updatePollEvents(fd);
		return;
	}
	ssize_t bytesSent = send(fd, client._outbuffer.c_str(),
			client._outbuffer.size() ,0);
	//signal a passer OU erreur send()
	if (bytesSent == -1) {
		if (errno == EAGAIN || errno == EWOULDBLOCK) {
			return;
		}
		clientIO_error("send() fail", fd);
		return;
	}
	//gestion envoi nul, partiel ou complet
	client._outbuffer.erase(0, (size_t)bytesSent);
	updatePollEvents(fd);
	/*
	//juste du debug qu'on pourra retirer a la fin du projet//////
	int buffSize = client._outbuffer.size();///////////////////////
	std::cout << "in clientIO: clientWrite" << std::endl;/////////
	std::cout << "From fd=" << fd << std::endl;///////////////////
	std::cout << "Bytes sent=" << bytesSent << std::endl;/////////
	std::cout << "_outbuffer size=" << buffSize << std::endl;//////
	std::cout << "_outbuffer: " << client._outbuffer << std::endl;/
	std::cout << std::endl;///////////////////////////////////////
	*/
}
