.PHONY:all clean
CC=gcc
SRC=$(wildcard *.c)
OBJ=$(patsubst %.c,%.o,$(SRC))
BIN=dlopen_test
all:$(BIN)
$(BIN):$(OBJ)
	$(CC) -o $@ $^ -ldl
%.o:%.c
	$(CC) -o $@ -c $<
clean:
	rm -rf $(BIN)
	rm -rf *.o

