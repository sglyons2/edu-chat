CC      = g++
CFLAGS  = -Wall
LDFLAGS = -lncurses

all: irc-chat

irc-chat: irc-chat.o ChatWindow.o Window.o IRCSocket.o
	$(CC) -o $@ $^ $(LDFLAGS)

irc-chat.o: irc-chat.cpp
	$(CC) -c $(CFLAGS) $<

ChatWindow.o: ChatWindow.cpp include/ChatWindow.hpp
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
