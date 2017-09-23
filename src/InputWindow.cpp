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
	delete this->window;
}

void InputWindow::refresh()
{
	wrefresh(this->window->window);
}

void __resize(Window *win, int h, int w, int by, int bx)
{
	win->height = h;
	win->width = w;
	win->begin_y = by;
	win->begin_x = bx;

	wclear(win->window);
	wresize(win->window, win->height, win->width);
	mvwin(win->window, win->begin_y, win->begin_x);
}

void InputWindow::resize(Window *parent)
{
	Window *window = this->window;

	// NOTE: InputWindow is highest priority for view,
	//       so can take up entire window.
	__resize(this->window,
	         std::min(window->height, std::max(parent->height, 3)),
	         parent->width,
	         parent->height-window->height,
	         0);
	this->print();
}

void InputWindow::formatMessage(std::vector<std::string>& lines, std::string line)
{
	size_t str_len = this->window->width-2;

	while (!line.empty()) {
		// simple solution atm, just throw it in at str_len
		// TODO: this, but better (space aware line change)
		if (line.length() > str_len) {
			std::string tmp = line.substr(0, str_len);
			line = line.substr(str_len);
			lines.push_back(tmp);
		} else {
			lines.push_back(line);
			line.clear();
		}
	}
}

void InputWindow::print()
{
	std::vector<std::string> lines;
	this->formatMessage(lines, this->text);

	size_t new_height = std::min(std::max((size_t) lines.size()+2, (size_t) 3),
	                             (size_t) this->window->height+this->window->begin_y);

	if (new_height != (size_t) this->window->height) {
		__resize(this->window,
		         new_height,
		         this->window->width,
		         this->window->begin_y-(new_height-this->window->height),
		         0);
	}

	this->window->print(lines, true);
}

void InputWindow::addCh(char c)
{
	this->text += c;
	this->print();
}

void InputWindow::delCh()
{
	this->text = this->text.substr(0, this->text.length()-1);
	wclear(this->window->window);
	this->print();
}

std::string InputWindow::getText()
{
	return this->text;
}

void InputWindow::clearText()
{
	this->text.clear();
	wclear(this->window->window);
	this->print();
}
