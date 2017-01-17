CC=gcc
SRC=$(wildcard *$(BIN)*.c)
OBJS=$(patsubst %.c,%.o,$(SRC))
BIN=matcher
%.o:%.c
	$(CC) -o $@ -g -Wall -c $<
$(BIN):$(OBJS)
	$(CC) -o $@  $^ -L. -lmatcherutils -lxmlcfg -lxml2
clean:
	rm -rf *.o
	rm -rf $(BIN) 
