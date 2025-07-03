#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "compress.h"
#include "bitfile.h"
#include "utils.h"

void test_compress_decompress() {
    // Create a dummy input file with a single character
    FILE *input_file = fopen("test_input.txt", "w+");
    fputc('a', input_file);
    fclose(input_file);

    // Compress the file
    input_file = fopen("test_input.txt", "r");
    FILE *compressed_file = fopen("test_compressed.bin", "wb+");
    BITFILE *output_bitfile = bitfile_open(compressed_file, 0);
    
    bitfile_close(output_bitfile);
    fclose(input_file);

    // Decompress the file
    fseek(compressed_file, 0, SEEK_SET);
    BITFILE *input_bitfile = bitfile_open(compressed_file, 0);
    FILE *decompressed_file = fopen("test_decompressed.txt", "w+");
    decompress(input_bitfile, decompressed_file);
    bitfile_close(input_bitfile);
    fclose(decompressed_file);

    // Compare original and decompressed files
    input_file = fopen("test_input.txt", "r");
    decompressed_file = fopen("test_decompressed.txt", "r");

    int original_char, decompressed_char;
    int match = 1;
    while ((original_char = fgetc(input_file)) != EOF && (decompressed_char = fgetc(decompressed_file)) != EOF) {
        if (original_char != decompressed_char) {
            match = 0;
            break;
        }
    }
    if (fgetc(input_file) != EOF || fgetc(decompressed_file) != EOF) {
        match = 0;
    }

    assert_true(match, "compress_decompress: original and decompressed files should match");

    fclose(input_file);
    fclose(decompressed_file);

    remove("test_input.txt");
    remove("test_compressed.bin");
    remove("test_decompressed.txt");
}

void test_compress() {
    test_compress_decompress();
}
