CC = g++
CFLAGS = -g -Wall -Wno-pointer-arith

TARGET = wav_editor

all: $(TARGET)

$(TARGET): $(TARGET).cpp
	$(CC) $(CFLAGS) -o $(TARGET).exe $(TARGET).cpp

clean: $(RM) $(TARGET)