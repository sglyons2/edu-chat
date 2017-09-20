#include <ncurses.h>
#include "include/Window.hpp"

Window::Window()
{
	this->current = newwin(LINES, COLS, 0, 0);

	wprintw(this->current, "Hello from the Window class!");
	wrefresh(this->current);
}

Window::~Window()
{
	delwin(this->current);
}
