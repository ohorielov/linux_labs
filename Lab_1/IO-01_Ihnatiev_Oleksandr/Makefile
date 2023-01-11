OBJ = WAVchanger.o
NAME = WAVchanger

all: $(NAME)

WAVchanger: $(OBJ)
	gcc $(OBJ) -lm -o $(NAME)

.c.o:
	gcc -c WAVchanger.c -o $(OBJ)

clean:
	rm -f *.o
	rm -f $(NAME)
