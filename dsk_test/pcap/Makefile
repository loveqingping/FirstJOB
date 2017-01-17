.PHONY:all clean
CC=gcc
CFLAGS=-g -Wall
LDFLAGS=-lpcap
BIN=mystack
SRC=$(wildcard *.c)
OBJS=$(patsubst %.c,%.o,$(SRC))
all:$(BIN)
%.o:%.c
	$(CC) -o $@ -g -Wall -c $<
$(BIN):$(OBJS)
	$(CC) -o $@ $^ $(LDFLAGS)
clean:
	rm -rf $(OBJS)
	rm -rf $(BIN)

