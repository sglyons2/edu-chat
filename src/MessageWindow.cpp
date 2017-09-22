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

void MessageWindow::formatMessage(std::vector<std::string>& lines, std::string line)
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

void MessageWindow::print()
{
	box(this->window->window, 0, 0);
	
	std::vector<std::string> lines;
	std::vector<std::string>::iterator it = this->text.begin();
	for (; it < this->text.end(); ++it) {
		this->formatMessage(lines, *it);
	}

	//size_t lines_begin = std::max((size_t) 0, lines.size()-(this->window->height-2));
	size_t lines_begin;
	if ((ssize_t) lines.size() < (ssize_t) this->window->height-2) {
		lines_begin = 0;
	} else {
		lines_begin = lines.size()-(this->window->height-2);
	}
	for (size_t i = 0; i < (size_t) this->window->height-2; ++i) {
		if (lines_begin+i >= lines.size())
			break;
		mvwprintw(this->window->window, i+1, 1, lines[lines_begin+i].c_str());
	}
}

void MessageWindow::addMessage(std::string msg)
{
	this->text.push_back(msg);
	this->print();
}

void MessageWindow::clearText()
{
	this->text.clear();
	wclear(this->window->window);
	this->print();
}
