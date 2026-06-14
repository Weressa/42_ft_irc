#ifndef CHANNEL_HPP
# define CHANNEL_HPP

# include <vector>
# include <string>

struct Channel {
	std::vector<int> _clientsFd;
	int              _operatorFd;
	std::string      _topic;

	Channel() : _clientsFd(), _operatorFd(-1), _topic("") {}
};

#endif
