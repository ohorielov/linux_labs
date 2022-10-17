SRC=$(wildcard ./src/*.c)
OBJ=$(patsubst ./src/%.c, ./src/%.o, $(SRC))

PROGRAM = ../build/wav_changer

$(PROGRAM): $(OBJ)
	gcc $^ -o $@ -lm

%.o: %.c
	gcc -c $< -o $@

cls:
	rm $(PROGRAM) $(OBJ)

start: $(PROGRAM)
	$(PROGRAM)
