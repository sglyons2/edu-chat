#ifndef EDUCHAT_HANDLER_HPP
#define EDUCHAT_HANDLER_HPP

#include <ctime>
#include <memory>
#include <string>
#include <vector>

namespace educhat {

	enum message_type { status_msg, log_msg, info_msg, err_msg };

	struct message {
		enum message_type type;
		std::string text;
		std::string owner;
		std::time_t timestamp;
	};

	class Handler {
	public:
		virtual void handleCommand(const std::string command) = 0;
		virtual bool isConnected() const = 0;
		virtual std::shared_ptr<message> getUpdate() = 0;
	};

	inline void split(std::string command, std::vector<std::string> &words)
	{
		std::size_t index = 0;

		do {
			auto index_beg = command.find_first_not_of(" \r\n\0", index);
			if (index_beg == std::string::npos) {
				break;
			}

			index = command.find_first_of(" \r\n\0", index_beg);
			if (index == std::string::npos) {
				words.push_back(command.substr(index_beg));
				break;
			}
			words.push_back(command.substr(index_beg, index-index_beg));
		} while (++index);
	};

} // namespace educhat

#endif
