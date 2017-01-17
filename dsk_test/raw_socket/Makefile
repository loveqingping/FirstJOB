.PHONY:all clean
CC=gcc
SRC=$(wildcard *.c)
OBJ=$(patsubst %.c, %.o, $(SRC))
BIN=raw_socket
all:$(BIN)
$(BIN):$(OBJ)
	$(CC) -o $@ $^ -lpcap
%.o:%.c
	$(CC) -o $@ -g -Wall -c $<
clean:
	rm -rf $(BIN)
	rm -rf $(OBJ)

