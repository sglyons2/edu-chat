#include <algorithm>
#include <cctype>

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

	void IrcHandler::handleCommand(const message &command)
	{
		// split to get first "word"?
		std::vector<std::string> words;

		split(command.text, words);

		// match first "word" to known command
		// run command as appropriate
		// refer to RFC 2812
		// TODO: actually fix. keep for quick implementation testing
		if (words.empty()) {
			return;
		}

		std::string first = words[0];
		std::transform(first.begin(), first.end(), first.begin(), ::tolower);

		if (first == "/connect" || first == "/c") {
			if (words.size() > 2) {
				socket->connect(words[1], words[2]);
			}
		} else if (first == "/join" || first == "/j") {
			if (words.size() > 1) {
				channel = words[1];
				socket->send("JOIN " + channel + "\r\n");
			}
		} else if (first == "/nick" || first == "/n") {
			if (words.size() > 1) {
				nick = words[1];
				socket->send("NICK " + nick + "\r\n");
			}
		} else if (first == "/user" || first == "/u") {
			if (words.size() > 4) {
				user = words[1];
				std::string irc_user_command = "USER " + user + " " +
				                               words[2] + " " +
						     	       words[3] + " " +
						     	       words[4] + " :";
				for (std::size_t i = 5; i < words.size()-1; ++i) {
						irc_user_command += words[i] + " ";
				}
				irc_user_command += words[words.size()-1] + "\r\n";
				socket->send(irc_user_command);
			}
		} else {
			socket->send("PRIVMSG " + command.owner + " :" + command.text + "\r\n");
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
		if (!received.empty()) {
			// one received can have multiple messages
			std::vector<std::string> lines;
			split(received, lines, "\r\n");
	
			for (auto line : lines) {
				// process message. create a message and put in messages if neeeded
				std::vector<std::string> words;
				split(line, words);
				std::string first = words[0];
				if (first == "PING") {
					socket->send("PONG\r\n");
				} else {
					std::shared_ptr<message> res(new message);
					res->type = log_msg;
					res->text = line;
					res->owner = "channel";
					time(&res->timestamp);
					messages.push_back(res);
				}
			}
		}

		// take a message from messages, send it back
		std::shared_ptr<message> msg = nullptr;
		if (!messages.empty()) {
			// handle message from socket
			// refer to RFC 2812
			// TODO: actually fix. keeping for quick implementation testing
			msg = messages.front();
			messages.pop_front();
		}

		// return struct message pointer
		return msg;
	}

} // namespace educhat
