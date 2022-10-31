CC = gcc
CFLAGS = -g -Wall
LFLAGS = -lm

SRCS = main.c wav.c
OBJS = $(SRCS:.c=.o)

TARGET = ../build/lab1

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJS)
$(CC) $^ -o $@ $(LFLAGS)

.o: .c
$(CC) $(CFLAGS) $(INCLUDES) -o $@ -c $<

clean:
$(RM) $(TARGET) $(OBJS)
