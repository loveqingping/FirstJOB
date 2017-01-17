.PHONY:all clean
SRC=cfg.c
OBJ=cfg.o
BIN=libreadinf.a
all:$(BIN)
$(BIN):$(OBJ)
	ar -crv $@ $^
clean:
	rm $(BIN)
	rm $(OBJ)
