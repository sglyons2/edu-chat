#include "include/IrcHandler.hpp"

namespace educhat {

	IrcHandler::IrcHandler(shared_ptr<Socket> sock)
	{
		socket = sock;
	}

	IrcHandler::~IrcHandler()
	{
		delete socket;
	}

	void IrcHandler::handleCommand(const std::string command)
	{
		// split to get first "word"?

		// match first "word" to known command
		// run command as appropriate
		if () {

		}
	}

	bool IrcHandler::isConnected()
	{
		return socket->isConnected();
	}

	std::shared_ptr<struct message> getUpdate()
	{
		// recv from socket
		// handle message from socket
		// return struct message pointer
	}

} // namespace educhat
