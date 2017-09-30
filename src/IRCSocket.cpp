#include <sys/types.h>
#include <sys/socket.h>
#include <sys/fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <netdb.h>
#include <string.h>
#include <cstdlib>
#include "include/IRCSocket.hpp"
#include <ncurses.h>

IRCSocket::IRCSocket()
{
	connected = false;
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	fcntl(sockfd, F_SETFL, O_NONBLOCK);
}

IRCSocket::~IRCSocket()
{
	FD_CLR(sockfd, &readfds);
	FD_CLR(sockfd, &writefds);
	close(sockfd);
}

void IRCSocket::connect(std::string server, std::string channel, std::string nickname)
{
	this->server = server;
	this->channel = channel;
	this->nickname = nickname;

	connect();
}

void IRCSocket::connect()
{
	struct addrinfo hints, *servinfo;
	memset(&hints, 0, sizeof hints);
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;

	int rv = getaddrinfo(server.c_str(), "6667", &hints, &servinfo);
	if (rv) {
		int e = errno;
		mvprintw(0, 0, "Error: getaddrinfo %d %d %s %s", rv, e, gai_strerror(rv), server.c_str());
		getch();
		exit(1);
	}

	rv = ::connect(sockfd, servinfo->ai_addr, servinfo->ai_addrlen);
	if (rv) {
		int e = errno;
		switch(e) {
			case EISCONN:
				connected = true;
				queue.push_back(std::string("NICK ")+nickname);
				queue.push_back(std::string("USER test test_ test__ :Testy McTest"));
				queue.push_back(std::string("JOIN ") + channel);
			case EAGAIN:
			case EALREADY:
			case EINPROGRESS:
				break;
			case ECONNREFUSED:
				break;
			default:
				// exception?
				exit(1);
				break;
		}
	} else {
		connected = true;
		queue.push_back(std::string("NICK ")+ nickname);
		queue.push_back(std::string("USER test test_ test__ :Testy McTest"));
		queue.push_back(std::string("JOIN ")+ channel);
	}

	freeaddrinfo(servinfo);
}

bool IRCSocket::isConnected()
{
	return connected;
}

#define MAXDATASIZE 512

void IRCSocket::send()
{
	if (isSetup() && !queue.empty()) {
		std::string current = queue.front() + "\r\n";
		queue.pop_front();
		int numbytes = ::send(sockfd, current.c_str(), current.length(), MSG_NOSIGNAL);
		if (numbytes == -1) {
			int e = errno;
			switch(e) {
				case EAGAIN:
					queue.push_front(current);
					break;
				default:
					exit(1);
					break;

			}
		} else {
			if (numbytes < (int) current.length()) {
				queue.push_front(current.substr(numbytes));
			}
		}
	}
}

void IRCSocket::send(std::string msg)
{
	// add msg to queue
	queue.push_back(msg);
	send();
}

bool IRCSocket::isSetup()
{
	return !server.empty() && !channel.empty() && !nickname.empty();
}
std::string IRCSocket::recv()
{
	if (!isSetup()) {
		return "";
	}
	if (!connected) {
		connect();
		return "";
	}

	char buf[MAXDATASIZE];
	int numbytes = ::recv(sockfd, buf, MAXDATASIZE-1, 0);
	if (numbytes == -1) {
		int e = errno;
		switch(e) {
			case EAGAIN:
				return std::string("");
				break;
			default:
				exit(1);
				break;
		}
	} else if (numbytes == 0) {
		connected = false;
		return std::string("");
	}
	buf[numbytes] = '\0';

	for (char *p = &buf[0]; *p != '\0'; p++) {
		if (*p == '\r' || *p == '\n')
			*p = ' ';
	}

	return std::string(buf);
}
