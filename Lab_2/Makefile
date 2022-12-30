CC = gcc

BINARY = main
SOURCES = *.c

.PHONY: all
all: $(BINARY)

$(BINARY): $(SOURCES)
	gcc $^ -o $(BINARY) -lm

.PHONY: clear
clear:
	rm -rf $(BINARY) *.o