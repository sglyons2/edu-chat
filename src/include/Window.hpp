#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <ncurses.h>

struct Window {
	WINDOW *window;
	int height;
	int width;
	int begin_y;
	int begin_x;

	Window(int height, int width, int begin_y, int begin_x);
	~Window();
};

#endif
