#ifndef CHATWINDOW_HPP
#define CHATWINDOW_HPP

#include "IRCSocket.hpp"
#include "Window.hpp"
#include <vector>
#include <string>
#include <ctime>

class Message {
private:
	time_t timestamp;
	std::string owner;
	std::string message;
public:
	Message(time_t timestamp, std::string owner, std::string message)
	{
		this->timestamp = timestamp;
		this->owner = owner;
		this->message = message;
	};
	time_t getTimestamp() { return timestamp; };
	std::string getOwner() { return owner; };
	std::string getMessage() { return message; };
};

class ChatWindow {
private:
	IRCSocket *socket;
	// To fix once I figure out how to format messages into an appropriate struct.
	bool showTime;
	std::vector<Message> messages; 
	std::string input;
	int cursor_y;
	int cursor_x;
	void drawMessages(Window *parent);
	void drawStatusBar(Window *parent);
	void drawInput(Window *parent);
	void saveCursor(Window *parent);
	void restoreCursor(Window *parent);
	void clearRows(Window *parent, int begin_y, int num_rows);
	void submitInput(Window *parent);
	void addMessage(std::string raw_msg);
public:
	ChatWindow();
	~ChatWindow();
	void draw(Window *parent);
	void refresh(Window *parent);
	void handleInput(Window *parent, int ch);
};

#endif
