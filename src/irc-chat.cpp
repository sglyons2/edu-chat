#include <cstdlib>
#include <ncurses.h>
#include "include/MainWindow.hpp"

int main(int argc, char **argv)
{
	initscr();
	raw();
	halfdelay(10);
	keypad(stdscr, TRUE);
	noecho();
	curs_set(0);

	MainWindow main_win;

	refresh();
	main_win.refresh();

	char ch;
	while ((ch = getch()) != 24u) {
		refresh();
		main_win.resize(LINES, COLS);
		main_win.refresh();
	}

	endwin();

	exit(EXIT_SUCCESS);
}
