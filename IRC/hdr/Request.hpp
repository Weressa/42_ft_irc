/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgrellie <lgrellie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 15:18:33 by lgrellie          #+#    #+#             */
/*   Updated: 2026/04/10 19:25:51 by vgodoy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REQUEST_HPP
# define REQUEST_HPP

#include <vector>
#include <string>

enum request_type
{
	INVALID,
	NICK,
	PASS,
	USER,
	PRIVMSG,
//	OPER, pas necessaire pour valider
	QUIT,
	JOIN,
	KICK,
	INVITE,
	TOPIC,
	MODE,
};

struct Request
{
		enum request_type	_type;		
		std::vector<std::string> _tokens;
		std::string	trailing;
};

#endif
