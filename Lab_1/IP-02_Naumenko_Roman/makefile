CC = g++
OBJECTS = main.o WavManager.o
FLAGS = 

ifeq ($(conf), d)
	FLAGS += -DDEBUG
else
	FLAGS += -DRELEASE
endif


main: $(OBJECTS)
	$(CC) $(FLAGS) -o main $(OBJECTS)
 
main.o: main.cpp WavManager.h
	$(CC) $(FLAGS) -c main.cpp WavManager.h

WavManager.o: WavManager.h WavManager.cpp LogMacros.h
	$(CC) $(FLAGS) -c WavManager.h WavManager.cpp LogMacros.h


clean: 
	rm main $(OBJECTS)

help:
	@echo 'conf: (optional)'
	@echo '	d - Add this flag to build project in debug configuration.'
