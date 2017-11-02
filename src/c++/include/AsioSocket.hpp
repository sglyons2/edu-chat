#ifndef EDUCHAT_ASIOSOCKET_HPP
#define EDUCHAT_ASIOSOCKET_HPP

#include <deque>
#include <mutex>
#include <string>
#include <thread>

#include <boost/asio.hpp>

#include "Socket.hpp"

#define RECVMSG_MAXLENGTH 512

namespace educhat {

	class AsioSocket : public Socket {
	public:
		AsioSocket();
		~AsioSocket();
		void reset();
		void connect(const std::string addr, const std::string port);
		bool isConnected() const;
		void send(const std::string msg);
		std::string recv();
	private:
		void doSend();
		void doRecv();
		boost::asio::io_service io_service;
		boost::asio::ip::tcp::socket socket;
		bool connected;
		std::thread *t;
		bool connect_in_progress;
		bool send_in_progress;
		bool recv_in_progress;
		std::deque<std::string> to_send;
		std::mutex to_send_m;
		char recv_msg[RECVMSG_MAXLENGTH];
		std::deque<std::string> to_recv;
		std::mutex to_recv_m;
	};

} // namespace educhat

#endif
