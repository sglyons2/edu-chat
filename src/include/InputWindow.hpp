#ifndef INPUTWINDOW_HPP
#define INPUTWINDOW_HPP

#include <ncurses.h>
#include "Window.hpp"
#include <string>

class InputWindow {
private:
	Window *window;
	std::string text;
public:
	InputWindow(Window *parent);
	~InputWindow();
	void resize(Window *parent);
	void refresh();
	void print();
	void addCh(char c);
};

#endif
