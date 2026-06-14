/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgrellie <lgrellie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 14:57:41 by lgrellie          #+#    #+#             */
/*   Updated: 2026/04/10 19:30:38 by vgodoy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Parser.hpp"

Parser::Parser( void )
{
};

Parser::Parser( Parser const & )
{
};

Parser::~Parser( void )
{
};

Parser const & Parser::operator=( Parser const & )
{
	return *this;
}

bool Parser::parseCommand(Client &client, Request &request) {
	std::string raw = this->getNextRawRequest(client);
	size_t pos;
	std::string	trailing = "";

	if (raw.empty())
		return false;

	pos = raw.find( " :");
	if (pos != std::string::npos) {
		trailing = raw.substr(pos + 2);
		raw = raw.substr(0, pos);
	}

	if (!this->parseRequest(raw, request))
		return false;

	request.trailing = trailing;
	return true;
}


std::string	Parser::getNextRawRequest( Client & client )
{
	size_t		first_cr_lf;
	std::string	raw_request;

	do
	{
		first_cr_lf = client._inbuffer.find( "\r\n" );
		if ( first_cr_lf == std::string::npos )
			return "";
		raw_request = client._inbuffer.substr( 0, first_cr_lf );
		client._inbuffer.erase( 0, first_cr_lf + 2 );
	} while ( raw_request.empty() && !client._inbuffer.empty() );
	return raw_request;
}


std::vector<std::string>	Parser::splitString( std::string str )
{

	std::vector<std::string>	split_str;
	std::istringstream			iss(str);
	std::string					word;

	split_str.clear();
	while ( iss >> word )
	{
		split_str.push_back( word );
	}
	return split_str;
}

bool Parser::parseRequest(const std::string &raw, Request &request)
{
	std::vector<std::string>	tokenized_request;
	tokenized_request = Parser::splitString(raw);

	if (tokenized_request.size() == 0)
		return false;
	request._tokens = tokenized_request;

	std::string &token = tokenized_request[0];
	if ( token == "NICK" )
	request._type = NICK;
	else if ( token == "PASS" )
		request._type = PASS;
	else if ( token == "USER" )
		request._type = USER;
	else if ( token == "PRIVMSG" )
		request._type = PRIVMSG;
//	else if ( token == "OPER" )
//		request._type = OPER;
	else if ( token == "QUIT" )
		request._type = QUIT;
	else if ( token == "JOIN" )
		request._type = JOIN;
	else if ( token == "KICK" )
		request._type = KICK;
	else if ( token == "INVITE" )
		request._type = INVITE;
	else if ( token == "TOPIC" )
		request._type = TOPIC;
	else if ( token == "MODE" )
		request._type = MODE;
	else
		request._type = INVALID;
	return true;
}
