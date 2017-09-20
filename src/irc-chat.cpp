#include <cstdlib>
#include <ncurses.h>

int main(int argc, char **argv)
{
	initscr();
	printw("Hello World!");
	refresh();
	getch();
	endwin();

	exit(EXIT_SUCCESS);
}
