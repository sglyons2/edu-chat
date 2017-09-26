#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include "Window.hpp"
#include "InputWindow.hpp"
#include "MessageWindow.hpp"
#include "IRCSocket.hpp"

class MainWindow {
private:
	InputWindow *input;
	MessageWindow *msg_win;
	Window *window;
	void print();
	IRCSocket *sock;
public:
	MainWindow();
	~MainWindow();
	void refresh();
	void resize(int height, int width);
	void addCh(char c);
	void delCh();
	std::string getInput();
};

#endif
