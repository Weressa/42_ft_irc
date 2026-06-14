#include "Server.hpp"
#include <iostream>

void Server::handleCommand(int fd, Request &request)
{
	if (request._type == PASS)
		handlePass(fd, request);
	else
		std::cout << "type not coded yet" << std::endl;
/*
	else if (request._type == NICK)
		handleNick(fd, request);
	else if (request._type == USER)
		handleUser(fd, request);
	else if (request._type == JOIN)
		handleJoin(fd, request);
	else if (request._type == PRIVMSG)
		handlePrivmsg(fd, request);
	else if (request._type == QUIT)
		handleQuit(fd, request);
	else if (request._type == KICK)
		handleKick(fd, request);
	else if (request._type == INVITE)
		handleInvite(fd, request);
	else if (request._type == TOPIC)
		handleTopic(fd, request);
	else if (request._type == MODE)
		handleMode(fd, request);
	*/
}

void Server::handlePass(int fd, Request &request)
{
	Client &client = _clients[fd];

	if (request._tokens.size() != 2) {
		Server::queueMessage(fd, "use: PASS password");
		}
	else if (request._tokens[1] == _password) {

		client._passOK = true;

		std::cout << "Client fd=[" << fd
				  << "] gave the GOOD password."
				  << std::endl;
		Server::queueMessage(fd, "You gave the GOOD password.");
		}
	else {
		Server::queueMessage(fd, "You gave a BAD passord.");
		}
}
