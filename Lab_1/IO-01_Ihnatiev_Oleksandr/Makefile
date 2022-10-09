OBJ = WAVchanger.o
NAME = WAVchanger

all: $(NAME)

WAVchanger: $(OBJ)
	gcc $(OBJ) -o $(NAME)

.c.o:
	gcc -c WAVchanger.c -o $(OBJ)

clean:
	rm -f *.o
	rm -f $(NAME)
