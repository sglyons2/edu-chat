#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <ncurses.h>
#include <vector>
#include <string>

struct Window {
	WINDOW *window;
	int height;
	int width;
	int begin_y;
	int begin_x;

	Window(int height, int width, int begin_y, int begin_x);
	~Window();
	void print(std::vector<std::string>& lines, bool boxed);
	void resize(int height, int width, int begin_y, int begin_x);
};

#endif
