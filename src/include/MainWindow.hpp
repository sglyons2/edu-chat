#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include "Window.hpp"
#include "InputWindow.hpp"
#include "MessageWindow.hpp"

class MainWindow {
private:
	InputWindow *input;
	MessageWindow *msg_win;
	Window *window;
	void print();
public:
	MainWindow();
	~MainWindow();
	void refresh();
	void resize(int height, int width);
	void addCh(char c);
	std::string getInput();
};

#endif
