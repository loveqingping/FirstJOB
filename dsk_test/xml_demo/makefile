CC=gcc
SRC=$(wildcard *$(BIN)*.c)
OBJS=$(patsubst %.c,%.o,$(SRC))
BIN=xml_demo
%.o:%.c
	$(CC) -o $@ -g -Wall -c $<
$(BIN):$(OBJS)
	$(CC) -o $@  $^ -L. -lxml2 -lxmlcfg
clean:
	rm -rf *.o
	rm -rf $(BIN) 
