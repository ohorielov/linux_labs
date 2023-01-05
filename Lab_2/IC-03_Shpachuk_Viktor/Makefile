TARGET = ../build/main
CC=gcc

PREF_SRC = ./src/

SRC=$(wildcard $(PREF_SRC)*.c)
OBJ=$(patsubst $(PREF_SRC)%.c, $(PREF_SRC)%.o, $(SRC))

$(TARGET): $(OBJ)
	mkdir ../build
	$(CC) $^ -o $@ -lm

%.o: %.c
	$(CC) -c $< -o $@

run: $(TARGET) 
	$(TARGET)

clean:
	rm $(TARGET) $(OBJ)
