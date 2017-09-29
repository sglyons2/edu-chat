#include <cstdlib>
#include <cctype>
#include <ncurses.h>
#include "include/MainWindow.hpp"
#include "include/ChatWindow.hpp"

void send(std::string msg)
{
	mvprintw(2, 0, "Sent Message: %s", msg.c_str());
}

int main(int argc, char **argv)
{
	initscr();
	raw();
	timeout(50);
	keypad(stdscr, TRUE);
	noecho();
	curs_set(0);

	Window *win = new Window(LINES, COLS, 0, 0);
	//MainWindow main_win;
	ChatWindow chat_win;
	chat_win.draw(win);

	wrefresh(win->window);
	//main_win.refresh();

	int ch;
	int old_LINES = LINES;
	int old_COLS = COLS;
	while ((ch = wgetch(win->window)) != 24u) { // Ctrl+x: exit
		if (isalnum(ch) || (isspace(ch) && ch != 10u) || ispunct(ch)) {
			chat_win.handleInput(win, ch);
			//main_win.addCh(ch);
		} else if (ch == 7u) {
			//main_win.delCh();	
		} else if (ch == 10u) { // Enter: send
			chat_win.handleInput(win, ch);
			//std::string msg = main_win.getInput();
			//send(msg);
		}

		if (old_LINES != LINES || old_COLS != COLS) {
			//main_win.resize(LINES, COLS);
			win->resize(LINES, COLS, 0, 0);
			chat_win.draw(win);
			old_LINES = LINES;
			old_COLS = COLS;
		}

		chat_win.draw(win);
		wrefresh(win->window);
	//	chat_win.refresh(win);
		//main_win.refresh();
	}

	delete win;
	endwin();

	exit(EXIT_SUCCESS);
}
