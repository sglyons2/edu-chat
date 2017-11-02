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
		sockfd = socket(AF_INET, SOCK_STREAM, 0);
		fcntl(sockfd, F_SETFL, O_NONBLOCK);
		reset_recently = true;
		t = nullptr;
		stop_thread = false;
	}

	void AsyncSocket::reset()
	{
		if (!reset_recently) {
			close(sockfd);
			connected = false;
			sockfd = socket(AF_INET, SOCK_STREAM, 0);
			fcntl(sockfd, F_SETFL, O_NONBLOCK);
			reset_recently = true;
		}
	}

	AsyncSocket::~AsyncSocket()
	{
		stop_thread = true;
		t->join(); // will this ever actually end? can we actually join?
		delete t;
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
			//int e = errno;
			// TODO: throw error for caller. we don't know UI
			return;
			exit(1);
		}

		rv = ::connect(sockfd, servinfo->ai_addr, servinfo->ai_addrlen);
		if (rv) {
			int e = errno;
			switch(e) {
				case EISCONN:
					connected = true;
					reset_recently = false;
					break;
				case EAGAIN:
				case EALREADY:
				case EINPROGRESS:
					connected = false;
					break;
				case ECONNREFUSED:
				default:
					// exception?
					break;
					exit(1);
					break;
			}
		} else {
			connected = true;
			reset_recently = false;
		}

		freeaddrinfo(servinfo);

		// t == nullptr should work.
		// if t exists, then all we should need is to connect and
		// doRecv and doSend should start working right after!
		if (connected && t == nullptr) {
			t = new std::thread([this]{ run(); });
		}
	}

	bool AsyncSocket::isConnected() const
	{
		return connected;
	}

	void AsyncSocket::run()
	{
		while(!stop_thread) {
			if (connected) {
				doSend();
				doRecv();	
			}
		}
	}

	#define MAXDATASIZE 512 // TODO: change as appropriate

	void AsyncSocket::send(const std::string msg)
	{
		if (!msg.empty()) {
			std::lock_guard<std::mutex> lock(to_send_m);
			to_send.push_back(msg);
		}
	}

	void AsyncSocket::doSend()
	{
		if (connected) {
			std::lock_guard<std::mutex> lock(to_send_m);
			if (!to_send.empty()) {
				const std::string msg = to_send.front();
				to_send.pop_front();
	
				int numbytes = ::send(sockfd, msg.c_str(), msg.length(), MSG_NOSIGNAL);
	
				if (numbytes == -1) {
					int e = errno;
					switch(e) {
						case EAGAIN:
							to_send.push_front(msg);
							break;
						default:
							// TODO: handle more and better
							exit(1);
							break;
					}
				} else {
					if (numbytes < (int) msg.length()) {
						to_send.push_front(msg.substr(numbytes));
					}
				}
			}
		}
	}

	std::string AsyncSocket::recv()
	{
		std::string msg = "";

		if (to_recv_m.try_lock()) {
			if (!to_recv.empty()) {
				msg = to_recv.front();
				to_recv.pop_front();
			}
			to_recv_m.unlock();
		}

		return msg;
	}

	void AsyncSocket::doRecv()
	{
		if (connected) {
			std::lock_guard<std::mutex> lock(to_recv_m);
			char buf[MAXDATASIZE];
			int numbytes = ::recv(sockfd, buf, MAXDATASIZE-1, 0);
			if (numbytes == -1) {
				int e = errno;
				switch(e) {
					case EAGAIN:
						break;
					default:
						// TODO: handle more and better
						exit(1);
						break;
				}
			} else if (numbytes == 0) {
				connected = false;
				reset();
			} else {
				buf[numbytes] = '\0';
				to_recv.push_back(buf);
			}
		}
	}

} // namespace educhat
