CC      = g++
CFLAGS  = -Wall
LDFLAGS = -lncurses

all: irc-chat

irc-chat: irc-chat.o MainWindow.o
	$(CC) -o $@ $^ $(LDFLAGS)

irc-chat.o: irc-chat.cpp
	$(CC) -c $(CFLAGS) $<

MainWindow.o: MainWindow.cpp include/MainWindow.hpp
	$(CC) -c $(CFLAGS) $<

.PHONY: clean cleanest

clean:
	rm *.o

cleanest: clean
	rm irc-chat
