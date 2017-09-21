#include "include/MainWindow.hpp"

MainWindow::MainWindow()
{
	this->window = new Window(LINES, COLS, 0, 0);
	this->print();
	this->msg_win = new MessageWindow(this->window);
	this->input = new InputWindow(this->window);
}

MainWindow::~MainWindow()
{
	delete this->input;
	delete this->msg_win;
	delete this->window;
}

void MainWindow::refresh()
{
	wrefresh(this->window->window);
	this->msg_win->refresh();
	this->input->refresh();
}

void MainWindow::resize(int height, int width)
{
	Window *window = this->window;

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
	mvwprintw(this->window->window, 0, 0, "Hello from the MainWindow class!");
}

void MainWindow::addCh(char c)
{
	this->input->addCh(c);
}

std::string MainWindow::getInput()
{
	std::string input = this->input->getText();
	this->input->clearText();

	this->msg_win->addMessage(input);

	return input;
}
