CC=gcc
CFLAGS=-Wall -Werror -Wextra -Wno-unused-function -Wno-unused-parameter -g
EXEC=main
SRC=src/
OUT_DIR=_build/
MKDIR_P = mkdir -p

all: directories $(EXEC)

.PHONY: directories

directories: ${OUT_DIR}

${OUT_DIR}:
	${MKDIR_P} ${OUT_DIR}

main: board.o ia.o main.o
	$(CC) -o main.d $(OUT_DIR)board.o $(OUT_DIR)ia.o $(OUT_DIR)main.o $(CFLAGS)

board.o: $(SRC)board.c $(SRC)board.h $(SRC)parameters.h
	$(CC) -o $(OUT_DIR)board.o -c $(SRC)board.c $(CFLAGS) -c

ia.o: $(SRC)ia.c $(SRC)ia.h $(SRC)parameters.h
	$(CC) -o $(OUT_DIR)ia.o -c $(SRC)ia.c $(CFLAGS) -c

main.o: $(SRC)main.c $(SRC)board.h $(SRC)ia.h $(SRC)parameters.h
	$(CC) -o $(OUT_DIR)main.o -c $(SRC)main.c $(CFLAGS) -c

clean:
	rm -rf *.o
	rm -rf $(OUT_DIR)
	rm -rf $(EXEC)