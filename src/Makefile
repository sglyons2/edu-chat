CC      = g++
CFLAGS  =
LDFLAGS = -lncurses

all: irc-chat

irc-chat: irc-chat.o
	$(CC) -o $@ $^ $(LDFLAGS)

irc-chat.o: irc-chat.cpp
	$(CC) -c $(CFLAGS) $<

.PHONY: clean cleanest

clean:
	rm *.o

cleanest: clean
	rm irc-chat
