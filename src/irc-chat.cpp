#include <cstdlib>
#include <ncurses.h>
#include "include/MainWindow.hpp"

void send(std::string msg)
{
	mvprintw(2, 0, "Sent Message: %s", msg.c_str());
}

int main(int argc, char **argv)
{
	initscr();
	halfdelay(10);
	raw();
	keypad(stdscr, TRUE);
	noecho();
	curs_set(0);

	MainWindow main_win;

	refresh();
	main_win.refresh();

	char ch;
	int old_LINES = LINES;
	int old_COLS = COLS;
	while ((ch = getch()) != 24u) { // Ctrl+x: exit
		if ((ch >= 'a' && ch <= 'z') ||
		    (ch >= 'A' && ch <= 'Z') ||
		    (ch >= '0' && ch <= '9')) {
			main_win.addCh(ch);
		} else if (ch == 10u) { // Enter: send
			std::string msg = main_win.getInput();
			//send(msg);
		}

		if (old_LINES != LINES || old_COLS != COLS) {
			main_win.resize(LINES, COLS);
			old_LINES = LINES;
			old_COLS = COLS;
		}
		refresh();
		main_win.refresh();
	}

	endwin();

	exit(EXIT_SUCCESS);
}
