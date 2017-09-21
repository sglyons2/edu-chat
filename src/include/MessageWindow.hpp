#ifndef MESSAGEWINDOW_HPP
#define MESSAGEWINDOW_HPP

#include <string>
#include "Window.hpp"

class MessageWindow {
private:
	Window *window;
	std::string text;
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
