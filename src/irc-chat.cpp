#include <cstdlib>
#include <ncurses.h>
#include "include/MainWindow.hpp"

int main(int argc, char **argv)
{
	initscr();
	cbreak();
	keypad(stdscr, TRUE);

	refresh();

	MainWindow main_win;

	getch();

	endwin();

	exit(EXIT_SUCCESS);
}
