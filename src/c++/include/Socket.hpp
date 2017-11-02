#ifndef EDUCHAT_SOCKET_HPP
#define EDUCHAT_SOCKET_HPP

#include <string>

namespace educhat {

	class Socket {
	public:
		virtual void reset() = 0;
		virtual void connect(const std::string addr, const std::string port) = 0;
		virtual bool isConnected() const = 0;
		virtual void send(const std::string msg) = 0;
		virtual std::string recv() = 0;
	};

} // namespace educhat

#endif
