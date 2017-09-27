#ifndef IRCSOCKET_HPP 
#define IRCSOCKET_HPP

#include <sys/select.h>
#include <string>
#include <deque>

class IRCSocket {
private:
	int sockfd;
	fd_set readfds;
	fd_set writefds;
	bool connected;
	bool isSet(fd_set *set);
	std::deque<std::string> queue;
public:
	IRCSocket();
	~IRCSocket();
	void connect();
	bool isConnected();
	std::string recv();
	void send(std::string msg);
	void send();
};

#endif
