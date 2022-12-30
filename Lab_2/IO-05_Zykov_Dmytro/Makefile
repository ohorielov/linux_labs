CC=gcc
CFLAGS=-std=c99 -Wall -Wextra -Werror -Wpedantic -Wno-unused-parameter

SRC=$(wildcard *.c)
OBJ=$(SRC:.c=.o)

BIN=huffman

.PHONY: release debug clean

release: CFLAGS+=-O3
release: $(BIN)

debug: CFLAGS+=-g -O0 -DDEBUG
debug: $(BIN)

$(BIN): $(OBJ)
	$(CC) $^ -o $@

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	$(RM) $(BIN) $(OBJ)
