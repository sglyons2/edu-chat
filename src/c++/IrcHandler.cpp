#include "include/IrcHandler.hpp"

namespace educhat {

	IrcHandler::IrcHandler(std::shared_ptr<Socket> sock)
	{
		socket = sock;
	}

	IrcHandler::~IrcHandler()
	{
		socket.reset();
	}

	void IrcHandler::handleCommand(const std::string command)
	{
		// split to get first "word"?
		std::vector<std::string> words;

		split(command, words);

		// match first "word" to known command
		// run command as appropriate
		// refer to RFC 2812
		// TODO: actually fix. keep for quick implementation testing
		if (words.empty()) {
			return;
		}

		if (words[0] == "/connect" || words[0] == "/c") {
			socket->connect("127.0.0.1", "6667");
		} else {
			socket->send(command);
		}
	}

	bool IrcHandler::isConnected() const
	{
		return socket->isConnected();
	}

	std::shared_ptr<message> IrcHandler::getUpdate()
	{
		// recv from socket TODO consider try/catch
		std::string received = socket->recv();
		if (received.empty()) {
			return nullptr;
		}

		if (received.substr(0, 4) == "PING") {
			socket->send("PONG\r\n");
			return nullptr;
		}

		std::shared_ptr<message> msg(new message);

		// handle message from socket
		// refer to RFC 2812
		// TODO: actually fix. keeping for quick implementation testing
		msg->type = log_msg;
		msg->text = received;
		msg->owner = "channel";
		time(&msg->timestamp);

		// return struct message pointer
		return msg;
	}

} // namespace educhat
