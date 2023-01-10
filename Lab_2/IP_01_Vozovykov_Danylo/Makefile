
CC :=cc
CFLAGS := -g -std=c99 -Wall -Werror
BUILDDIR := ../build
SRCDIR := ./src

all: main

main: $(BUILDDIR)/binaryTree.o $(BUILDDIR)/decoder.o $(BUILDDIR)/encoder.o $(BUILDDIR)/huffmanTree.o $(BUILDDIR)/priorityQueue.o $(BUILDDIR)/main.o
	$(CC) $^ -o $(BUILDDIR)/main

$(BUILDDIR)/%.o: $(SRCDIR)/%.c
	$(CC) -c $(CFLAGS) -o $@ $<

clean:
	rm -rf $(BUILDDIR)/*