#ifndef EDUCHAT_IRCHANDLER_HPP
#define EDUCHAT_IRCHANDLER_HPP

#include <memory>
#include <string>
#include <vector>

#include "Handler.hpp"
#include "Socket.hpp"

namespace educhat {

	class IrcHandler : public Handler {
	public:
		IrcHandler(std::shared_ptr<Socket> socket);
		~IrcHandler();
		void handleCommand(const std::string command);
		bool isConnected();
		std::shared_ptr<struct message> getUpdate();
	private:
		std::shared_ptr<Socket> socket;
	}

} // namespace educhat

#endif
