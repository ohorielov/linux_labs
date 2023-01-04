CC = gcc
CFLAGS = -Wall -Wextra -g

SRC = main.c huffman.c
OBJ = $(SRC:.c=.o)

all: lab2

lab2: $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f *.o lab2
