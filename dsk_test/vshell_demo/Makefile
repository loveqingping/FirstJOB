.PHONY:all clean
CC=gcc
CFLAGS=-g -Wall
CPPFLAGS=-I ../libshares/include
LDFLAGS=-L ../libshares/libs -lvshell -lpthread
SRC=$(wildcard *.c)
OBJ=$(patsubst %.c,%.o,$(SRC))
BIN=vshell_demo
all:$(BIN)
$(BIN):$(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)
%.o:%.c
	$(CC) -o $@ $(CFLAGS) $(CPPFLAGS) -c $<
clean:
	rm -rf $(BIN)
	rm -rf *.o

