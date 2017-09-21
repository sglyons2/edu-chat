#ifndef WINDOW_HPP
#define WINDOW_HPP

struct Window {
	WINDOW *window;
	int height;
	int width;
	int begin_y;
	int begin_x;

	Window(int height, int width, int begin_y, int begin_x)
	{
		this->window = newwin(height, width, begin_y, begin_x);
		this->height = height;
		this->width = width;
		this->begin_y = begin_y;
		this->begin_x = begin_x;
	}
};

#endif
