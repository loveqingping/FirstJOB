.PHONY:all clean
CC=gcc
SRC=$(wildcard *.c)
OBJS=$(patsubst %.c,%.o,$(SRC))
CPPFLAGS= -I .
LDFLAGS=-lpthread
CFLAGS=-g -Wall
BIN=thread_pool
all:$(BIN)
$(BIN):$(OBJS)
	$(CC) -o $@ $^ $(LDFLAGS)
%.o:%.c
	$(CC) -o $@ $(CPPFLAGS) $(CFLAGS) -c $<
clean:
	rm -rf $(BIN)
	rm -rf $(OBJS)
