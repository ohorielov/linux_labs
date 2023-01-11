result : main.o wav.o
	gcc -o Changer main.o wav.o

main.o : main.c
	gcc -c main.c -o main.o

wav_handle.o : wav.c
	gcc -c wav.c -o wav.o

clean:
	rm Changer *.o