CC=clang
CFLAGS=-std=c11 -g -Wall -Wextra -Werror -Wpedantic -Wno-unused-parameter
INCLUDES=-Isrc
LDFLAGS=

SRC=$(wildcard src/*.c)
OBJ=$(SRC:.c=.o)

BIN=../build/lab

.PHONY: all run clean

all: $(BIN)

run: all
	./$(BIN)

$(BIN): $(OBJ)
	$(CC) $^ -o $@ $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $< $(INCLUDES)

clean:
	$(RM) $(BIN) $(OBJ)