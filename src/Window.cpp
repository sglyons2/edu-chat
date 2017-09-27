#include "include/Window.hpp"

Window::Window(int height, int width, int begin_y, int begin_x)
{
	this->window = newwin(height, width, begin_y, begin_x);
	this->height = height;
	this->width = width;
	this->begin_y = begin_y;
	this->begin_x = begin_x;
}

Window::~Window()
{
	delwin(this->window);
}

void Window::print(std::vector<std::string>& lines, bool boxed = false)
{
	wclear(window);

	if (boxed) {
		box(this->window, 0, 0);
	}

	ssize_t lines_begin;
	ssize_t max_lines = this->height - (boxed ? 2 : 0);
	ssize_t size_lines = lines.size();
	if (size_lines < max_lines) {
		lines_begin = 0;
	} else {
		lines_begin = size_lines - max_lines;
	}

	for (ssize_t i = 0; i < max_lines && lines_begin+i < size_lines; ++i) {
		mvwprintw(this->window, i+(boxed?1:0), (boxed?1:0), lines[lines_begin+i].c_str());
	}
}
