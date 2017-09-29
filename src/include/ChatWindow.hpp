#include "IRCSocket.hpp"
#include "Window.hpp"
#include <vector>
#include <string>

class ChatWindow {
private:
	IRCSocket socket;
	// To fix once I figure out how to format messages into an appropriate struct.
	std::vector<std::string> messages; 
	std::string input;
	int cursor_y;
	int cursor_x;
	void drawMessages(Window *parent);
	void drawStatusBar(Window *parent);
	void drawInput(Window *parent);
	void saveCursor(Window *parent);
	void restoreCursor(Window *parent);
	void clearRows(Window *parent, int begin_y, int num_rows);
	void addMessage(std::string raw_msg);
public:
	ChatWindow();
	~ChatWindow();
	void draw(Window *parent);
	void refresh(Window *parent);
	void handleInput(Window *parent, char ch);
};
