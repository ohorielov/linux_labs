BUILD_DIR = ../build
CC = g++

SRC_DIR = src
SRC_FILES = $(wildcard $(SRC_DIR)/*.cpp)

OBJS = $(SRC_FILES)
OBJ_NAME = ${BUILD_DIR}/main

COMPILER_FLAGS = -Wall -O0 -g -lm

all:
	$(CC) $(OBJS) -o $(OBJ_NAME) $(COMPILER_FLAGS)