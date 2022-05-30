CC = gcc
CFLAGS = -g -Wall # Flag to pass to gcc
CPPFLAGS = -I./include -Og -D DEBUG # Flag to pass to the C preprocessor

all: main
main: build/main.o build/counter.o build/priorityqueue.o build/huffman.o build/compress.o build/bitfile.o
	$(CC) $(CFLAGS) build/main.o build/counter.o build/priorityqueue.o build/huffman.o build/compress.o build/bitfile.o -o jip
build/main.o: src/main.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c src/main.c -o build/main.o
build/counter.o: include/counter.h src/counter.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c src/counter.c -o build/counter.o
build/priorityqueue.o: include/priorityqueue.h src/priorityqueue.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c src/priorityqueue.c -o build/priorityqueue.o
build/huffman.o: include/huffman.h src/huffman.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c src/huffman.c -o build/huffman.o
build/compress.o: include/compress.h src/compress.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c src/compress.c -o build/compress.o
build/bitfile.o: include/bitfile.h src/bitfile.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c src/bitfile.c -o build/bitfile.o

test: buildtest
	./test.out
buildtest: build/test_main.o build/counter.o build/priorityqueue.o build/biginteger.o
	$(CC) $(CFLAGS) build/test_main.o build/counter.o build/priorityqueue.o build/biginteger.o -o test.out
build/test_main.o: test/test_main.c test/utils.c test/test_counter.c test/test_priorityqueue.c test/test_biginteger.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c test/test_main.c -o build/test_main.o

clean:
	rm -rf build/* jip test.out
