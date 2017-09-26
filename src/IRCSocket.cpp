#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <errno.h>
#include <netdb.h>
#include <string.h>
#include <cstdlib>
#include "include/IRCSocket.hpp"

//using select for handling the socket

IRCSocket::IRCSocket()
{
	connected = false;
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	/*
	FD_ZERO(&readfds);
	FD_ZERO(&writefds);
	FD_SET(sockfd, &readfds);
	FD_SET(sockfd, &writefds);
	*/
	// select goes into main loop?
}

IRCSocket::~IRCSocket()
{
	/*
	FD_CLR(sockfd, &readfds);
	FD_CLR(sockfd, &writefds);
	*/
	close(sockfd);
}

void IRCSocket::connect()
{
	struct addrinfo hints, *servinfo;
	memset(&hints, 0, sizeof hints);
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;

	int rv = getaddrinfo("127.0.0.1", "6667", &hints, &servinfo);
	if (rv) {
		exit(1);
	}

	rv = ::connect(sockfd, servinfo->ai_addr, servinfo->ai_addrlen);
	if (rv) {
		int e = errno;
		switch(e) {
			case EISCONN:
				connected = true;
			case EALREADY:
				break;
			default:
				// exception?
				exit(1);
				break;
		}
	} else {
		connected = true;
	}

	freeaddrinfo(servinfo);
}

bool IRCSocket::isConnected()
{
	return connected;
}

void IRCSocket::recv()
{
//if (FD_ISSET(socketfd, &readfds)) {
//recv
//0 connection closed
//EAGAIN or EWOULDBLOCK, nothing yet, try later
//}
}

void IRCSocket::send()
{
//if (FD_ISSET(socketfd, &writefds)) {
//add msg attribute
//send
//EAGAIN or EWOULDBLOCK if message doesn't fit into send buffer
//use of select for determining when it is possible to send more data?
//consider using MSG_NOSIGNAL flag to prevent SIGPIPE signal on closed connection
//   returns EPIPE error anyways
//think about partial sends, a queue may be helpful
//}
}
