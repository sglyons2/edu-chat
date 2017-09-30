#include <cstdlib>
#include <cctype>
#include <ncurses.h>
#include "include/ChatWindow.hpp"

int main(int argc, char **argv)
{
	initscr();
	noecho();
	//curs_set(0);
	raw();
	start_color();
	use_default_colors();

	Window *win = new Window(LINES, COLS, 0, 0);
	keypad(win->window, TRUE);
	wtimeout(win->window, 1);

	ChatWindow chat_win;
	chat_win.draw(win);

	wrefresh(win->window);

	int ch;
	int old_LINES = LINES;
	int old_COLS = COLS;
	while ((ch = wgetch(win->window)) != 24u) { // Ctrl+x: exit
		if (isalnum(ch) || (isspace(ch) && ch != 10u) || ispunct(ch)) {
			chat_win.handleInput(win, ch);
		} else if (ch == 7u) { // Backspace
			chat_win.handleInput(win, ch);
		} else if (ch == 10u) { // Enter: send
			chat_win.handleInput(win, ch);
		} else {
			chat_win.handleInput(win, ch);
		}

		if (old_LINES != LINES || old_COLS != COLS) {
			win->resize(LINES, COLS, 0, 0);
			chat_win.draw(win);
			old_LINES = LINES;
			old_COLS = COLS;
		}

		chat_win.refresh(win);
		wrefresh(win->window);
	}

	delete win;
	endwin();

	exit(EXIT_SUCCESS);
}
