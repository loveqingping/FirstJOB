CC=gcc
SRC=$(wildcard *.c)
OBJ=$(patsubst %.c, %.o, $(SRC))
MARCO=
CFLAG=-g3 -Wall
CPPFLAG=
LINK=
OPTIMIZE=-pg
BIN=test
all:$(BIN)
$(BIN):$(OBJ)
	$(CC) -o $@ $(OPTIMIZE) $^ $(LINK)
%.o:%.c
	$(CC) -o $@ $(MARCO) $(CFLAG) $(OPTIMIZE) $(CPPFLAG) -c $<  
clean:
	rm $(BIN)
	rm $(OBJ)
