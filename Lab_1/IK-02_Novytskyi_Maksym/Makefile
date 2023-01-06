output: main.o wav_processing.o
	gcc main.o wav_processing.o -o wave

main.o: main.c
	gcc -c main.c

wav_processing.o: wav_processing.c wav_processing.h
	gcc -c wav_processing.c

clean:
	rm *.o wave