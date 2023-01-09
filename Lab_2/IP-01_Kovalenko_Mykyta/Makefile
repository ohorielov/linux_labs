CC :=cc
CFLAGS := -g -std=c99 -Wall -Werror
BUILDDIR := ../build
SRCDIR := ./src

all: main

main: $(BUILDDIR)/huffman.o $(BUILDDIR)/main.o
	$(CC) $^ -o $(BUILDDIR)/main

$(BUILDDIR)/%.o: $(SRCDIR)/%.c
	$(CC) -c $(CFLAGS) -o $@ $<

clean:
	rm -rf $(BUILDDIR)/*
