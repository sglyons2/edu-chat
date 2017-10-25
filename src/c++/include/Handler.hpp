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

} // namespace educhat

#endif
