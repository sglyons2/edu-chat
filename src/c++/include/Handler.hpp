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
		virtual void handleCommand(const message &command) = 0;
		virtual bool isConnected() const = 0;
		virtual std::shared_ptr<message> getUpdate() = 0;
	};

	inline void split(const std::string s, std::vector<std::string> &to, const std::string delimiters = " ")
	{
		std::size_t index = 0;

		do {
			auto index_beg = s.find_first_not_of(delimiters, index);
			if (index_beg == std::string::npos) {
				break;
			}

			index = s.find_first_of(delimiters, index_beg);
			if (index == std::string::npos) {
				to.push_back(s.substr(index_beg));
				break;
			}
			to.push_back(s.substr(index_beg, index-index_beg));
		} while (true);
	};

} // namespace educhat

#endif
