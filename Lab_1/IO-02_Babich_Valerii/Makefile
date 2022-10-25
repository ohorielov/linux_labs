result : main.o wav.o
	gcc -o wav_changer main.o wav.o 

main.o : main.c
	gcc -c main.c -o main.o

wav.o : wav_handle.c
	gcc -c wav.c -o wav_handle.o

clean: 
	rm wav_changer *.o