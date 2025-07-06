CC = gcc
CFLAGS = -g -Wall -fprofile-arcs -ftest-coverage # Flag to pass to gcc
CPPFLAGS = -I./include -I./test -Og -D DEBUG # Flag to pass to the C preprocessor

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
buildtest: build/test_main.o build/test_counter.o build/test_priorityqueue.o build/test_huffman.o build/test_compress.o build/test_bitfile.o build/counter.o build/priorityqueue.o build/huffman.o build/compress.o build/bitfile.o build/utils.o
	$(CC) $(CFLAGS) build/test_main.o build/test_counter.o build/test_priorityqueue.o build/test_huffman.o build/test_compress.o build/test_bitfile.o build/counter.o build/priorityqueue.o build/huffman.o build/compress.o build/bitfile.o build/utils.o -o test.out
build/utils.o: test/utils.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c test/utils.c -o build/utils.o
build/test_main.o: test/test_main.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c test/test_main.c -o build/test_main.o
build/test_counter.o: test/test_counter.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c test/test_counter.c -o build/test_counter.o
build/test_priorityqueue.o: test/test_priorityqueue.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c test/test_priorityqueue.c -o build/test_priorityqueue.o
build/test_huffman.o: test/test_huffman.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c test/test_huffman.c -o build/test_huffman.o
build/test_compress.o: test/test_compress.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c test/test_compress.c -o build/test_compress.o
build/test_bitfile.o: test/test_bitfile.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c test/test_bitfile.c -o build/test_bitfile.o

clean:
	rm -rf build/* jip test.out

coverage:
	$(MAKE) clean
	$(MAKE) CFLAGS='-g -Wall --coverage' test
	gcov -o build/ src/*
