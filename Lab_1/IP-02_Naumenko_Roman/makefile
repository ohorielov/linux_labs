# variables
CC = g++
OBJECTS = main.o WavHandler.o
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
 
main.o: main.cpp WavHandler.h Macroses.h
	$(CC) $(FLAGS) -c main.cpp WavHandler.h Macroses.h

WavHandler.o: WavHandler.h WavHandler.cpp Macroses.h
	$(CC) $(FLAGS) -c WavHandler.h WavHandler.cpp Macroses.h

# targets
clean: 
	rm main $(OBJECTS) *.gch *.wav

help:
	@echo 'conf: (optional)'
	@echo '	d - Add this parametr to build project in debug configuration.'
