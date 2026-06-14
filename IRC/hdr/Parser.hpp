/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgrellie <lgrellie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 15:43:36 by lgrellie          #+#    #+#             */
/*   Updated: 2026/04/10 19:57:17 by vgodoy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_HPP
# define PARSER_HPP

# include <string>
# include <iostream>
# include <sstream>
# include <vector>
# include "Request.hpp"
# include "Client.hpp"

class Parser
{

	public:
		Parser( void );
		Parser( Parser const & to_copy );
		~Parser( void );
		Parser const &	operator=( Parser const & rhs );


		bool parseCommand(Client &client, Request &request);
		static std::string getNextRawRequest( Client & client );
		static std::vector<std::string>	splitString( std::string str );
		bool parseRequest(const std::string &raw, Request &request);

};

#endif
