#ifndef MESSAGEWINDOW_HPP
#define MESSAGEWINDOW_HPP

#include <string>
#include <vector>
#include "Window.hpp"

class MessageWindow {
private:
	Window *window;
	std::vector<std::string> text;
	void formatMessage(std::vector<std::string>& lines, std::string line);
public:
	MessageWindow(Window *parent);
	~MessageWindow();
	void resize(Window *parent);
	void refresh();
	void print();
	void addMessage(std::string msg);
	void clearText();
};

#endif
