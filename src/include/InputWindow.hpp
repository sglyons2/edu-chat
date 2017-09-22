#ifndef INPUTWINDOW_HPP
#define INPUTWINDOW_HPP

#include <ncurses.h>
#include "Window.hpp"
#include <string>
#include <vector>

class InputWindow {
private:
	Window *window;
	std::string text;
	void formatMessage(std::vector<std::string>& lines, std::string line);
	void print();
public:
	InputWindow(Window *parent);
	~InputWindow();
	void resize(Window *parent);
	void refresh();
	void addCh(char c);
	void delCh();
	std::string getText();
	void clearText();
};

#endif
