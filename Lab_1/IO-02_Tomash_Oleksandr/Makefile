wav_run : main.o header.o
	gcc main.o header.o -o wav_run
main.o : main.c
	gcc -c main.c -o main.o
header.o : header.c
	gcc -c header.c -o header.o
clean : 
	rm wav_run edited.wav *.o