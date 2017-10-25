#ifndef EDUCHAT_HANDLER_HPP
#define EDUCHAT_HANDLER_HPP

#include <string>
#include <vector>

namespace educhat {

	class Handler {
	public:
		virtual void handleCommand(const std::string command) = 0;
		virtual bool isConnected() const = 0;
		virtual void updateLog(const std::vector<std::string> &messages) = 0;
	}

} // namespace educhat

#endif
