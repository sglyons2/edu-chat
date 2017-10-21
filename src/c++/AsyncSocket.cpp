#include <sys/types.h>
#include <sys/socket.h>
#include <sys/fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <netdb.h>
#include <string.h>
#include <cstdlib>

#include "include/AsyncSocket.hpp"

namespace educhat {

	AsyncSocket::AsyncSocket()
	{
		connected = false;
		send_rdy = false;
		recv_rdy = false;
		sockfd = socket(AF_INET, SOCK_STREAM, 0);
		fcntl(sockfd, F_SETFL, O_NONBLOCK);
	}

	AsyncSocket::~AsyncSocket()
	{
		close(sockfd); // consider if error occurs and does it matter?
	}

	void AsyncSocket::connect(const std::string addr, const std::string port)
	{
		struct addrinfo hints, *servinfo;
		memset(&hints, 0, sizeof(hints));
		hints.ai_family = AF_UNSPEC;
		hints.ai_socktype = SOCK_STREAM;

		int rv = getaddrinfo(addr.c_str(), port.c_str(), &hints, &servinfo);
		if (rv) {
			int e = errno;
			// TODO: throw error for caller. we don't know UI
			exit(1);
		}

		rv = ::connect(sockfd, servinfo->ai_addr, servinfo->ai_addrlen);
		if (rv) {
			int e = errno;
			switch(e) {
				case EISCONN:
					connected = true;
					send_rdy = true;
					recv_rdy = true;
				case EAGAIN:
				case EALREADY:
				case EINPROGRESS:
					break;
				case ECONNREFUSED:
				default:
					// exception?
					exit(1);
					break;
			}
		} else {
			connected = true;
			send_rdy = true;
			recv_rdy = true;
		}

		freeaddrinfo(servinfo);
	}

	bool AsyncSocket::isConnected() const
	{
		return connected;
	}

	#define MAXDATASIZE 512 // TODO: change as appropriate

	void AsyncSocket::send(const std::string msg)
	{
		if (!msg.empty())
			queue.push_back(msg);
		send();
	}

	void AsyncSocket::send()
	{
		if (isConnected() && send_rdy && !queue.empty()) {
			const std::string msg = queue.front();
			queue.pop_front();

			int numbytes = ::send(sockfd, msg.c_str(), msg.length(), MSG_NOSIGNAL);

			if (numbytes == -1) {
				int e = errno;
				switch(e) {
					case EAGAIN:
						queue.push_front(msg);
						break;
					default:
						// TODO: handle more and better
						exit(1);
						break;
				}
			} else {
				if (numbytes < (int) msg.length()) {
					queue.push_front(msg.substr(numbytes));
				}
			}
		}
	}

	std::string AsyncSocket::recv()
	{
		if (!isConnected() || !recv_rdy) {
			return ""; // TODO: can i improve this?
		}

		char buf[MAXDATASIZE];
		int numbytes = ::recv(sockfd, buf, MAXDATASIZE-1, 0);
		if (numbytes == -1) {
			int e = errno;
			switch(e) {
				case EAGAIN:
					return "";
				default:
					// TODO: handle more and better
					exit(1);
					break;
			}
		} else if (numbytes == 0) {
			connected = false;
			return "";
		}

		buf[numbytes] = '\0';

		return buf;
	}

} // namespace educhat
