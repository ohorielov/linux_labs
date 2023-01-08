CC = gcc
CFLAGS = -Wall -Wextra -O2

SRC = main.c 
OBJ = $(SRC:.c=.o)

all: lab1

lab1: $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f *.o lab1
