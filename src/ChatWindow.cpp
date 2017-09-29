#include "include/ChatWindow.hpp"
#include <cctype>

unsigned messages_draw_counter = 0;

ChatWindow::ChatWindow()
{
	// Will use entire space that parent has, so SAVE IT~
	// Will be drawing line by line, so no need to create a window
	// Can consider showing a cursor and keeping track of it
	// to save, modify, then restore afterwards
	// Create socket? Get ready?
	socket = new IRCSocket();
}

ChatWindow::~ChatWindow()
{
	// erase all chat info
	delete socket;
}

void ChatWindow::draw(Window *parent)
{
	saveCursor(parent);
	drawMessages(parent);
	drawStatusBar(parent);
	drawInput(parent);
	restoreCursor(parent);
	// refresh is parent's responsibility after draw
}

void ChatWindow::drawMessages(Window *parent)
{
	clearRows(parent, 0, parent->height-2);

	// draw last parent->rows-2 lines of messages
	// Convert messages to lines until fill up last parent->rows-2 lines
	// Draw lines
	if (!messages.empty()) {
		mvwprintw(parent->window, 0, 0, messages.back().c_str());
	} else {
		mvwprintw(parent->window, 0, 0, "messages");
	}
}

void ChatWindow::drawStatusBar(Window *parent)
{
	clearRows(parent, parent->height-2, 1);
	mvwprintw(parent->window, parent->height-2, 0, "status");
	// limit info based on cols/width
	// Priority:
	//  1) Channel
	//  2) Server
	//  3) Nickname
	//  4) Time
	//  Channel, Server, Nickname can be taken from IRCSocket?
}

void ChatWindow::drawInput(Window *parent)
{
	clearRows(parent, parent->height-1, 1);

	// Use horizontal scrolling to have it consistent and usable
	std::string visible;

       	if ((int) input.length() < parent->width-5) {
		visible = input;
	} else {
		// TODO: support left<->right scrolling.
		// gotta introduce cursor watching stuff for that.
		visible = input.substr(input.length()-(parent->width-5));
	}

	if (visible.empty()) {
		visible = "input";
	}

	mvwprintw(parent->window, parent->height-1, 0, visible.c_str());
}

void ChatWindow::saveCursor(Window *parent)
{
	getyx(parent->window, cursor_y, cursor_x);
}

void ChatWindow::restoreCursor(Window *parent)
{
	wmove(parent->window, cursor_y, cursor_x);
}

void ChatWindow::clearRows(Window *parent, int begin_y, int num_lines)
{
	for (int i = 0; i < num_lines; i++) {
		wmove(parent->window, begin_y+i, 0);
		wclrtoeol(parent->window);
	}
}

void ChatWindow::refresh(Window *parent)
{
	// technically is parent's refresh, but we can also do work here~
	// do a lot of the work here
	drawStatusBar(parent); // update time and status every time
}

// Working with Input! Parent takes care of some, but not all! Passes the rest here!
// Submit input for processing
void ChatWindow::handleInput(Window *parent, int ch)
{
	switch(ch) {
		case KEY_ENTER:
		case 10u:
			// Refine this
			addMessage(input);
			input.clear();
			draw(parent);
			break;
		default:
			if (isalnum(ch) || ch == ' ') {
				input += ch;
				drawInput(parent);
			}
	}
}

// Adding Messages!
void ChatWindow::addMessage(std::string raw_msg)
{
	// refine this with IRC specifics or run it through something like IRCFormatter
	messages.push_back(raw_msg);
}
