main : main.o FileReader.o
	g++ -o main main.o FileReader.o
 
main.o : main.cpp FileReader.h
	g++ -c main.cpp FileReader.h

FileReader.o : FileReader.h FileReader.cpp
	g++ -c FileReader.h FileReader.cpp
	
clean : 
	rm main main.o FileReader.o