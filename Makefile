# OBJS specifies which files to compile as part of the project
OBJS = ./src/main.c ./src/median.c ./src/pgm.c
# CC specifies which compiler we're using
CC = gcc
# COMPILER_FLAGS specifies the additional compilation
# optons we're using
COMPILER_FLAGS = -Wall
# LINKER_FLAGS specifies the libraries we're linking against

# OBJ_NAME specifies the name of our executable
OBJ_NAME = ./src/kadai
# This is the target that compiles our executable
# デフォルトだとmacのフラグを使う
all : $(OBJS)
	$(CC) $(OBJS) $(COMPILER_FLAGS) -o $(OBJ_NAME)
