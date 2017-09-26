#ifndef IRCSOCKET_HPP 
#define IRCSOCKET_HPP

#include <sys/select.h>

class IRCSocket {
private:
	int sockfd;
	fd_set readfds;
	fd_set writefds;
	bool connected;
public:
	IRCSocket();
	~IRCSocket();
	void connect();
	bool isConnected();
	void recv();
	void send();
};

/*
const struct timeval timeout = {
	.tv_sec = 0,
	.tv_usec = 0,
};
*/

#endif
