#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <ncurses.h>
#include "Window.hpp"
#include "InputWindow.hpp"

class MainWindow {
private:
	InputWindow *input;
	Window *window;
public:
	MainWindow();
	~MainWindow();
	void refresh();
	void resize(int height, int width);
	void print();
	void addCh(char c);
	std::string getInput();
};

#endif
