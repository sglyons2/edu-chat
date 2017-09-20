#include <cstdlib>
#include <ncurses.h>
#include "include/MainWindow.hpp"

int main(int argc, char **argv)
{
	initscr();
	raw();
	keypad(stdscr, TRUE);
	noecho();

	refresh();

	MainWindow main_win;

	char ch;
	while ((ch = getch()) != 24u) {
		// do stuff
	}

	endwin();

	exit(EXIT_SUCCESS);
}
