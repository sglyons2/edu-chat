CC      = g++
CFLAGS  = -Wall
LDFLAGS = -lncurses

all: irc-chat

irc-chat: irc-chat.o MainWindow.o InputWindow.o MessageWindow.o Window.o \
          IRCSocket.o
	$(CC) -o $@ $^ $(LDFLAGS)

irc-chat.o: irc-chat.cpp
	$(CC) -c $(CFLAGS) $<

MainWindow.o: MainWindow.cpp include/MainWindow.hpp
	$(CC) -c $(CFLAGS) $<

InputWindow.o: InputWindow.cpp include/InputWindow.hpp
	$(CC) -c $(CFLAGS) $<

MessageWindow.o: MessageWindow.cpp include/MessageWindow.hpp
	$(CC) -c $(CFLAGS) $<

Window.o: Window.cpp include/Window.hpp
	$(CC) -c $(CFLAGS) $<

IRCSocket.o: IRCSocket.cpp include/IRCSocket.hpp
	$(CC) -c $(CFLAGS) $<

.PHONY: clean cleanest

clean:
	rm *.o

cleanest: clean
	rm irc-chat
