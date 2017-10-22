#ifndef EDUCHAT_ASYNCSOCKET_HPP
#define EDUCHAT_ASYNCSOCKET_HPP

#include <deque>
#include <string>
#include "Socket.hpp"


namespace educhat {

	class AsyncSocket : public Socket {
	public:
		AsyncSocket();
		~AsyncSocket();
		void connect(const std::string addr, const std::string port);
		bool isConnected() const;
		void send(const std::string msg);
		std::string recv();
	private:
		int sockfd;
		bool connected;
		bool send_rdy;
		bool recv_rdy;
		void send();
		std::deque<std::string> to_send;
	};

} // namespace educhat

#endif
