# variables
CC = g++
OBJECTS = main.o WavManager.o
FLAGS = 

# cmd args
conf ?= r 

ifeq ($(conf), d)
	FLAGS += -DDEBUG
else
	FLAGS += -DRELEASE
endif

# build commands
main: $(OBJECTS)
	$(CC) $(FLAGS) -o main $(OBJECTS)
 
main.o: main.cpp WavManager.h
	$(CC) $(FLAGS) -c main.cpp WavManager.h

WavManager.o: WavManager.h WavManager.cpp LogMacros.h
	$(CC) $(FLAGS) -c WavManager.h WavManager.cpp LogMacros.h

# targets
clean: 
	rm main $(OBJECTS) *.gch *.wav

help:
	@echo 'conf: (optional)'
	@echo '	d - Add this parametr to build project in debug configuration.'
