CC := gcc
CFLAGS := -Wall
BUILDDIR := ../build

wav_processor: $(BUILDDIR)/wav_processor.o $(BUILDDIR)/main.o
	$(CC) $(CFLAGS) $(BUILDDIR)/wav_processor.o $(BUILDDIR)/main.o -o $(BUILDDIR)/wav_processor

$(BUILDDIR)/wav_processor.o: wav_processor.c
	$(CC) -c $(CFLAGS) wav_processor.c -o $(BUILDDIR)/wav_processor.o

$(BUILDDIR)/main.o: main.c
	$(CC) -c $(CFLAGS) main.c -o $(BUILDDIR)/main.o

clean:
	rm -rf $(BUILDDIR)/wav_processor* $(BUILDDIR)/main.o

