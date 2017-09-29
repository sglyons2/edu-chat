#include "Window.hpp"

class IRCWindow {
private:
	void drawMessages(Window *parent);
	void drawStatusBar(Window *parent);
	void drawInput(Window *parent);
public:
	IRCWindow();
	~IRCWindow();
	void draw(Window *parent);
	void refresh(Window *parent);
};
