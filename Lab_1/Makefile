resultName := "Volume changer"
result: main.o wavProcessor.o
	gcc -o $(resultName) main.o wavProcessor.o 

main.o : main.c
	gcc -c main.c -o main.o

wav_handle.o : wavProcessor.c
	gcc -c wavProcessor.c -o wavProcessor.o

clean: 
	rm $(resultName) *.o
