output: main.o wav_processor.o
	gcc main.o wav_processor.o -o wave

main.o: main.c
	gcc -c main.c

wav_processor.o: wav_processor.c wav_processor.h
	gcc -c wav_processor.c

clean:
	rm *.o wave
