CC := gcc
CFLAGS := -g -std=c99 -Wall -Werror
BUILDDIR := ./
SRCDIR := ./



all: $(BUILDDIR)/tree.o $(BUILDDIR)/main.o
	$(CC) $^ -o $(BUILDDIR)/main

$(BUILDDIR)/%.o: $(SRCDIR)/%.c
	$(CC) -c $(CFLAGS) -o $@ $<

clean:
	rm -rf $(BUILDDIR)/*
