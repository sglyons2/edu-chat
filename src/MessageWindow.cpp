#include "include/MessageWindow.hpp"

MessageWindow::MessageWindow(Window *parent)
{
	this->window = new Window(parent->height-4, parent->width, 1, 0);
	this->print();
}

MessageWindow::~MessageWindow()
{
	delete this->window;
}

void MessageWindow::refresh()
{
	wrefresh(this->window->window);
}

void MessageWindow::resize(Window *parent)
{
	Window *window = this->window;

	window->height = parent->height-4;
	window->width = parent->width;
	window->begin_y = 1;
	window->begin_x = 0;

	wclear(window->window);
	wresize(window->window, window->height, window->width);
	mvwin(window->window, window->begin_y, window->begin_x);
	this->print();
}

void MessageWindow::print()
{
	box(this->window->window, 0, 0);
	// TODO: this, but better
	mvwprintw(this->window->window, 1, 1, this->text.c_str());
}

void MessageWindow::addMessage(std::string msg)
{
	// TODO: this, but better
	this->text += msg;
	this->print();
}

void MessageWindow::clearText()
{
	this->text.clear();
	wclear(this->window->window);
	this->print();
}
