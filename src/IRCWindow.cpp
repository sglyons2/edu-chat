#include "include/IRCWindow.hpp"

IRCWindow::IRCWindow()
{
	// Will use entire space that parent has, so SAVE IT~
	// Will be drawing line by line, so no need to create a window
	// Can consider showing a cursor and keeping track of it
	// to save, modify, then restore afterwards
}

IRCWindow::~IRCWindow()
{

}

// Resizes are now done by the parent, to the parent's window,
// and then passed to a IRCWindow's draw call. Very simple~
// Removes a lot of levels, simplifies what the IRCWindow knows about.
void IRCWindow::draw(Window *parent)
{
	drawMessages(parent);
	drawStatusBar(parent);
	drawInput(parent);
	refresh(parent);
}

void IRCWindow::drawMessages(Window *parent)
{
	// clear rows
	// draw last parent.rows - 2 lines of messages
}

void IRCWindow::drawStatusBar(Window *parent)
{
	// clear rows
	// limit info based on cols/width
	// Priority:
	//  1) Channel
	//  2) Server
	//  3) Nickname
	//  4) Time
}

void IRCWindow::drawInput(Window *parent)
{
	// clear rows
	// Use horizontal scrolling to have it consistent and usable

}

void IRCWindow::refresh(Window *parent)
{
	// technically is parent's refresh, but we can also do work here~
}
