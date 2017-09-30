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
	bool isSetup();
public:
	std::string server;
	std::string channel;
	std::string nickname;
	IRCSocket();
	~IRCSocket();
	void connect(std::string server, std::string channel, std::string nickname);
	void connect();
	bool isConnected();
	std::string recv();
	void send(std::string msg);
	void send();
};

#endif
