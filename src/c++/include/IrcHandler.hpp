#ifndef EDUCHAT_IRCHANDLER_HPP
#define EDUCHAT_IRCHANDLER_HPP

#include <deque>
#include <memory>
#include <string>

#include "Handler.hpp"
#include "Socket.hpp"

namespace educhat {

	class IrcHandler : public Handler {
	public:
		IrcHandler(std::shared_ptr<Socket> socket);
		~IrcHandler();
		void handleCommand(const message &command);
		bool isConnected() const;
		std::shared_ptr<message> getUpdate();
	private:
		std::shared_ptr<Socket> socket;
		std::string channel;
		std::string user;
		std::string nick;
		std::deque<std::shared_ptr<message>> messages;
	};

} // namespace educhat

#endif
