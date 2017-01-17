.PHONY:all clean
CC=gcc
SRC=$(wildcard *.c)
OBJ=$(patsubst %.c, %.o, $(SRC))
BIN=http_client
all:$(BIN)
$(BIN):$(OBJ)
	$(CC) -o $@ $^ -lpcap -lpthread
%.o:%.c
	$(CC) -o $@ -g -Wall -c $<
clean:
	rm -rf $(BIN)
	rm -rf $(OBJ)

