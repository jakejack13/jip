CC = gcc
CFLAGS = -g -Wall # Flag to pass to gcc
CPPFLAGS = -I. -D DEBUG # Flag to pass to the C preprocessor

all: main
main: main.o heap.o
main.o: main.c 
heap.o: heap.h heap.c
clean:
	rm -rf *.dSYM *.o main
