resultName := "WavChanger"
 result: main.o WavChanger.o
	gcc -o $(resultName) main.o WavChanger.o 

main.o : main.c
	gcc -c main.c -o main.o

wav_handle.o : WavChanger.c
	gcc -c WavChanger.c -o WavChanger.o

clean: 
	rm $(resultName) *.o
