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

test: buildtest
	./test.out
buildtest: build/test_main.o build/counter.o
	$(CC) $(CFLAGS) build/test_main.o build/counter.o -o test.out
build/test_main.o: test/test_main.c test/utils.c test/test_counter.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c test/test_main.c -o build/test_main.o

clean:
	rm -rf build/* main test.out
