

result : main.o wav_handler.o
	gcc -o result main.o wav_handle.o 

main.o : main.c
	gcc -c main.c -o main.o

wav_handle.o : wav_handle.c
	gcc -c wav_handle.c wav_handle.o

clean: 
	rm AlexWavChanger *.o