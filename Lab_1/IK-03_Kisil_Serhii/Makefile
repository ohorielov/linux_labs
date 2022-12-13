resultName := "changerwav"
 result: main.o changerwav.o
	gcc -o $(resultName) main.o changerwav.o 

main.o : main.c
	gcc -c main.c -o main.o

wav_handle.o : changerwav.c
	gcc -c changerwav.c -o changerwav.o

clean: 
	rm $(resultName) *.o