#ifndef CLIENT_HPP
# define CLIENT_HPP

# define CHANNELS_JOINED_MAX 10
# define MAX_INBUFFER_SIZE  (1 << 13) //2^13 -> 8KB
# define MAX_OUTBUFFER_SIZE (1 << 16) //2^16 -> 64KB

#include <string>
#include <cstddef>
#include <vector>

struct   Client
{
		int    _fd;

    	std::string    _inbuffer;
    	std::string    _outbuffer;

		std::string _username;
		std::string _nickname;

		bool _passOK;
		bool _registered;
		
		std::vector<std::string> _channels;

		Client() : _fd(-1), _inbuffer(""), _outbuffer(""),
				   _username(""), _nickname(""),
				   _passOK(false), _registered(false) {}
};

std::ostream &    operator<<(std::ostream & o, Client const & c);

#endif
