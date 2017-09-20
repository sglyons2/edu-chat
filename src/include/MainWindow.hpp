#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <ncurses.h>

class MainWindow {
private:
	WINDOW *current;
public:
	MainWindow();
	~MainWindow();
};

#endif
