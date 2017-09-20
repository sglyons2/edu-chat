#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <ncurses.h>

class Window {
private:
	WINDOW *current;
public:
	Window();
	~Window();
};

#endif
