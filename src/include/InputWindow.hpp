#ifndef INPUTWINDOW_HPP
#define INPUTWINDOW_HPP

#include <ncurses.h>
#include "Window.hpp"

class InputWindow {
private:
	Window *window;
public:
	InputWindow(Window *parent);
	~InputWindow();
	void resize(Window *parent);
	void refresh();
	void print();
};

#endif
