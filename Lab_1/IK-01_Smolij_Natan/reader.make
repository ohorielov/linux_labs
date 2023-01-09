OBJ_FOLDER=obj
EXECUTABLE = reader
SOURCE_FILES := $(wildcard *.c)
OBJECT_FILES := $(SOURCE_FILES:%.c=$(OBJ_FOLDER)/%.o)

all:reader
reader: $(OBJ_FOLDER) $(OBJECT_FILES)
	gcc  -o $(EXECUTABLE) $(OBJECT_FILES) -lm

$(OBJ_FOLDER)/%.o:%.c
	echo $(OBJECT_FILES)
	gcc -c $< -o $@

$(OBJ_FOLDER):
	mkdir $(OBJ_FOLDER)
clean:
	rm $(OBJECT_FILES) $(EXECUTABLE) 
	rmdir $(OBJ_FOLDER)
