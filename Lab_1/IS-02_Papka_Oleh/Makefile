BUILD_DIR = build
CC = gcc

SRC_FILES = $(wildcard *.c)

OBJS = $(SRC_FILES)
OBJ_NAME = ../$(BUILD_DIR)/main

COMPILER_FLAGS = -Wall -O0 -g -lm

all:
	$(CC) $(OBJS) -o $(OBJ_NAME) $(COMPILER_FLAGS)