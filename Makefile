CC = gcc
CFLAGS = -g -Wall # Flag to pass to gcc
CPPFLAGS = -I./include -O # Flag to pass to the C preprocessor

all: main
main: build/counter.o build/main.o
	$(CC) $(CFLAGS) build/main.o build/counter.o -o main
build/main.o: src/main.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c src/main.c -o build/main.o
build/counter.o: include/counter.h src/counter.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c src/counter.c -o build/counter.o
clean:
	rm -rf build/*
