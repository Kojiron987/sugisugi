# OBJS specifies which files to compile as part of the project
OBJS = Pgm.cpp
MAIN = $(OBJS) main.cpp
KADAI2 = $(OBJS) Kadai2.cpp median.c
# CC specifies which compiler we're using
CC = g++
# COMPILER_FLAGS specifies the additional compilation
# optons we're using
COMPILER_FLAGS = -std=c++0x -Wall

# OBJ_NAME specifies the name of our executable
OBJ_NAME = kadai
OBJ_KADAI2 = kadai2
# This is the target that compiles our executable
all : $(MAIN)
	$(CC) $(MAIN) $(COMPILER_FLAGS) -o $(OBJ_NAME)
kadai2: $(KADAI2)
	$(CC) $(KADAI2) $(COMPILER_FLAGS) -o $(OBJ_KADAI2)
