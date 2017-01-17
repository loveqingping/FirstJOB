.PHONY:all clean
CC=gcc
CFLAGS=-g -Wall
LDFLAGS=-lpthread
SRC=$(wildcard *.c)
OBJ=$(patsubst %.c,%.o,$(SRC))
BIN=http_test
all:$(BIN)
$(BIN):$(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)
%.o:%.c
	$(CC) -o $@ $(CFLAGS) -c $<
clean:
	rm -rf *.o
	rm -rf $(BIN)

