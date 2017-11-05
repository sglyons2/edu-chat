#ifndef EDUCHAT_ASYNCSOCKET_HPP
#define EDUCHAT_ASYNCSOCKET_HPP

// namespace std
#include <deque>      // deque
#include <mutex>      // mutex
#include <string>     // string
#include <thread>     // thread

// namespace educhat
#include "Socket.hpp" // Socket


namespace educhat {

	class AsyncSocket : public Socket {
	public:
		AsyncSocket();
		~AsyncSocket();
		// Resets the socket, usually for a new connection.
		void reset();
		void connect(const std::string addr, const std::string port);
		bool isConnected() const;
		void send(const std::string msg);
		std::string recv();
	private:
		int sockfd;
		bool reset_recently;
		bool connected;
		std::deque<std::string> to_send;
		std::deque<std::string> to_recv;
		std::thread *t;
		bool stop_thread;
		std::mutex to_send_m;
		std::mutex to_recv_m;
		void run(struct addrinfo *servinfo);
		void stopThread();
		void doConnect(struct addrinfo *servinfo);
		void doSend();
		void doRecv();
	};

} // namespace educhat

#endif
