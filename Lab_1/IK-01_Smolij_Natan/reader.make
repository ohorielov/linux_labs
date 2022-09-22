all:reader

reader: reader.o my_lib.o
	gcc -o reader reader.o my_lib.o
reader.o:reader.c
	gcc -c reader.c
my_lib.o:my_lib.c
	gcc -c my_lib.c

clean:
	rm -rf *.o reader
