GCC=gcc
FLAGS=-Wall -pedantic -std=c11
FILES=src/*.c
EXEC=maze
EXECD=maze_debug
LIBS=-lGL -lGLU -lglfw -lm

all:
	$(GCC) $(FLAGS) $(FILES) -o bin/$(EXEC) $(LIBS)

debug:
	$(GCC) $(FLAGS) -g -DDEBUG $(FILES) -o bin/$(EXECD) $(LIBS)
