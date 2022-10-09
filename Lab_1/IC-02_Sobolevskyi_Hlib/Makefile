BUILD_DIR = build/
CC = gcc

SRC_DIR = src
SRC_FILES = $(wildcard $(SRC_DIR)/*.c)

OBJS = $(SRC_FILES)
OBJ_NAME = main

COMPILER_FLAGS = -Wall -O0 -g

all:
	$(CC) $(OBJS) -o $(OBJ_NAME) $(COMPILER_FLAGS)