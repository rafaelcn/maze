GCC=gcc
FLAGS=-Wall -pedantic -std=c11
FILES=*.c
EXEC=maze
EXECD=maze_debug
LIBS=-lGL -lGLU -lglfw -lm

all:
	$(GCC) $(FLAGS) $(FILES) -o $(EXEC) $(LIBS)

debug:
	$(GCC) $(FLAGS) -g -DDEBUG $(FILES) -o $(EXECD) $(LIBS)
