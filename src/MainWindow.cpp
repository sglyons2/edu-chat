#include "include/MainWindow.hpp"

MainWindow::MainWindow()
{
	this->window = new Window(LINES, COLS, 0, 0);
	this->print();
	this->msg_win = new MessageWindow(this->window);
	this->input = new InputWindow(this->window);
	sock = new IRCSocket();
	sock->connect();
}

MainWindow::~MainWindow()
{
	delete sock;
	delete this->input;
	delete this->msg_win;
	delete this->window;
}

void MainWindow::refresh()
{
	print();
	wrefresh(window->window);
	this->msg_win->refresh();
	this->input->refresh();
}

void MainWindow::resize(int height, int width)
{
	wclear(window->window);
	window->height = height;
	window->width = width;
	wresize(window->window, window->height, window->width);
	this->print();

	this->msg_win->resize(window);
	this->input->resize(window);
}

void MainWindow::print()
{
	std::string status = "Not connected";
	if (sock && sock->isConnected()) {
		status = "Connected";
	}
	wmove(window->window, 0, 0);
	wclrtoeol(window->window);
	wrefresh(window->window);
	mvwprintw(window->window, 0, 0, status.c_str());
}

void MainWindow::addCh(char c)
{
	this->input->addCh(c);
}

void MainWindow::delCh()
{
	this->input->delCh();
	this->msg_win->resize(this->window);
	this->input->resize(this->window);
}

std::string MainWindow::getInput()
{
	std::string input = this->input->getText();
	this->input->clearText();

	this->msg_win->addMessage(input);

	return input;
}
