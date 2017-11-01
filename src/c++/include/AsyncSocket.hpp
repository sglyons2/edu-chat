#ifndef EDUCHAT_ASYNCSOCKET_HPP
#define EDUCHAT_ASYNCSOCKET_HPP

#include <deque>
#include <mutex>
#include <string>
#include <thread>

#include "Socket.hpp"


namespace educhat {

	class AsyncSocket : public Socket {
	public:
		AsyncSocket();
		~AsyncSocket();
		void init();
		void connect(const std::string addr, const std::string port);
		bool isConnected() const;
		void send(const std::string msg);
		std::string recv();
	private:
		int sockfd;
		bool connected;
		std::mutex connected_m;
		std::deque<std::string> to_send;
		std::deque<std::string> to_recv;
		std::thread *t;
		bool stop_thread;
		std::mutex to_send_m;
		std::mutex to_recv_m;
		void run();
		void doSend();
		void doRecv();
	};

} // namespace educhat

#endif
