CC      = g++
CFLAGS  = -Wall
LDFLAGS = -lncurses

all: irc-chat

irc-chat: irc-chat.o Window.o
	$(CC) -o $@ $^ $(LDFLAGS)

irc-chat.o: irc-chat.cpp
	$(CC) -c $(CFLAGS) $<

Window.o: Window.cpp include/Window.hpp
	$(CC) -c $(CFLAGS) $<

.PHONY: clean cleanest

clean:
	rm *.o

cleanest: clean
	rm irc-chat
