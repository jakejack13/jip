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
    
    // Call compress function
    compress(input_file, output_bitfile);
    bitfile_close(output_bitfile);
    fclose(input_file);

    // Decompress the file
    rewind(compressed_file);
    int bits_in_last_byte_read = fgetc(compressed_file);
    BITFILE *input_bitfile = bitfile_open(compressed_file, bits_in_last_byte_read);
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

void test_compress_empty_file() {
    // Create an empty input file
    FILE *input_file = fopen("test_empty_input.txt", "w+");
    fclose(input_file);

    // Compress the empty file
    input_file = fopen("test_empty_input.txt", "r");
    FILE *compressed_file = fopen("test_empty_compressed.bin", "wb+");
    BITFILE *output_bitfile = bitfile_open(compressed_file, 0);
    int bits_in_last_byte = compress(input_file, output_bitfile);
    bitfile_close(output_bitfile);
    fclose(input_file);

    // Write bits_in_last_byte to the beginning of the compressed file
    fseek(compressed_file, 0, SEEK_SET);
    fputc(bits_in_last_byte, compressed_file);

    // Decompress the empty file
    rewind(compressed_file);
    int bits_in_last_byte_read = fgetc(compressed_file);
    BITFILE *input_bitfile = bitfile_open(compressed_file, bits_in_last_byte_read);
    FILE *decompressed_file = fopen("test_empty_decompressed.txt", "w+");
    decompress(input_bitfile, decompressed_file);
    bitfile_close(input_bitfile);
    fclose(decompressed_file);

    // Verify that the decompressed file is empty
    decompressed_file = fopen("test_empty_decompressed.txt", "r");
    fseek(decompressed_file, 0, SEEK_END);
    long file_size = ftell(decompressed_file);
    assert_equals_int(0, file_size, "test_compress_empty_file: decompressed file should be empty");
    fclose(decompressed_file);

    remove("test_empty_input.txt");
    remove("test_empty_compressed.bin");
    remove("test_empty_decompressed.txt");
}

void test_compress() {
    test_compress_decompress();
    test_compress_empty_file();
}
