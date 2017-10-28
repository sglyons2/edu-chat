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
		bool isConnected() const;
		std::shared_ptr<message> getUpdate();
	private:
		std::shared_ptr<Socket> socket;
		std::string channel;
		std::string user;
		std::string nick;
	};

} // namespace educhat

#endif
