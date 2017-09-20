#include <ncurses.h>
#include "include/MainWindow.hpp"

MainWindow::MainWindow()
{
	this->current = newwin(LINES, COLS, 0, 0);

	wprintw(this->current, "Hello from the MainWindow class!");
	wrefresh(this->current);
}

MainWindow::~MainWindow()
{
	delwin(this->current);
}
