CC = gcc

BINARY = volumeChanger
SOURCES = *.c

.PHONY: all
all: $(BINARY)

$(BINARY): $(SOURCES)
	gcc $^ -o $(BINARY)

.PHONY: clear
clear:
	rm -rf $(BINARY) *.o