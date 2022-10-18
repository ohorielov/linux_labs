BIN = ../build/wav_changer
SOURCE=$(wildcard ./src/*.c)
OBJECTF=$(patsubst ./src/%.c, ./src/%.o, $(SOURCE))

$(BIN): $(OBJECTF)
	gcc $^ -o $@ -lm

%.o: %.c
	gcc -c $< -o $@

run: $(BIN)
	$(BIN)

clean:
	rm $(BIN) $(OBJECTF)
