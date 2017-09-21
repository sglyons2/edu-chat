#include <algorithm>
#include "include/InputWindow.hpp"

InputWindow::InputWindow(Window *parent)
{
	int height = 3;
	this->window = new Window(height, parent->width, parent->height-height, 0);
	this->print();
}

InputWindow::~InputWindow()
{
	delwin(this->window->window);
}

void InputWindow::refresh()
{
	wrefresh(this->window->window);
}

void InputWindow::resize(Window *parent)
{
	Window *window = this->window;

	// NOTE: InputWindow is highest priority for view,
	//       so can take up entire window.
	window->height = std::min(window->height, parent->height);
	window->width = parent->width;
	window->begin_y = parent->height-window->height;
	window->begin_x = 0;

	wclear(window->window);
	wresize(window->window, window->height, window->width);
	mvwin(window->window, window->begin_y, window->begin_x);
	this->print();
}

void InputWindow::print()
{
	box(this->window->window, 0, 0);
	mvwprintw(this->window->window, 1, 1, this->text.c_str());
}

void InputWindow::addCh(char c)
{
	this->text += c;
}
