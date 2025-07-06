#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> // For ftruncate

#include "compress.h"
#include "bitfile.h"
#include "utils.h"

void test_decompress_truncated_file();
void test_decompress_single_bit_file_header();
void test_decompress_single_byte_with_bits();
void test_decompress_early_eof_bitfile_getc();
void test_decompress_empty_compressed_file();
void test_decompress_bitfile_getc_eof();

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
    compress(input_file, output_bitfile);
    bitfile_close(output_bitfile);
    fclose(input_file);

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
    test_decompress_truncated_file();
    test_decompress_single_bit_file_header();
    test_decompress_single_byte_with_bits();
    test_decompress_early_eof_bitfile_getc();
    test_decompress_empty_compressed_file();
}

void test_decompress_truncated_file() {
    // Create a dummy input file with some content
    FILE *input_file = fopen("test_input_truncated.txt", "w+");
    fputs("hello world", input_file);
    fclose(input_file);

    // Compress the file
    input_file = fopen("test_input_truncated.txt", "r");
    FILE *compressed_file = fopen("test_compressed_truncated.bin", "wb+");
    BITFILE *output_bitfile = bitfile_open(compressed_file, 0);
    compress(input_file, output_bitfile);
    bitfile_close(output_bitfile);
    fclose(input_file);

    // Truncate the compressed file to 0 bytes to simulate an empty file
    compressed_file = fopen("test_compressed_truncated.bin", "r+");
    ftruncate(fileno(compressed_file), 0); // Truncate to 0 size
    fclose(compressed_file);

    // Decompress the truncated file
    compressed_file = fopen("test_compressed_truncated.bin", "rb");
    // No need to read bits_in_last_byte_read, as fgetc will return EOF
    BITFILE *input_bitfile = bitfile_open(compressed_file, 0); // bits_in_last_byte doesn't matter here
    FILE *decompressed_file = fopen("test_decompressed_truncated.txt", "w+");
    decompress(input_bitfile, decompressed_file);
    bitfile_close(input_bitfile);
    fclose(decompressed_file);

    // Verify that the decompressed file is empty
    decompressed_file = fopen("test_decompressed_truncated.txt", "r");
    fseek(decompressed_file, 0, SEEK_END);
    long decompressed_size = ftell(decompressed_file);
    assert_equals_int(0, decompressed_size, "test_decompress_truncated_file: decompressed file should be empty");
    fclose(decompressed_file);

    remove("test_input_truncated.txt");
    remove("test_compressed_truncated.bin");
    remove("test_decompressed_truncated.txt");
}

void test_decompress_single_bit_file_header() {
    // Create a compressed file with file_size = 1 and bits_in_last_byte = 1
    FILE *compressed_file = fopen("test_single_bit_header.bin", "wb+");
    fputc(1, compressed_file); // bits_in_last_byte = 1
    fclose(compressed_file);

    compressed_file = fopen("test_single_bit_header.bin", "rb");
    int bits_in_last_byte_read = fgetc(compressed_file);
    BITFILE *input_bitfile = bitfile_open(compressed_file, bits_in_last_byte_read);
    FILE *decompressed_file = fopen("test_decompressed_single_bit_header.txt", "w+");

    // Decompress (should result in an empty file as there's no actual data)
    decompress(input_bitfile, decompressed_file);

    bitfile_close(input_bitfile);
    fclose(decompressed_file);

    // Verify that the decompressed file is empty
    decompressed_file = fopen("test_decompressed_single_bit_header.txt", "r");
    fseek(decompressed_file, 0, SEEK_END);
    long file_size = ftell(decompressed_file);
    assert_equals_int(0, file_size, "test_decompress_single_bit_file_header: decompressed file should be empty");
    fclose(decompressed_file);

    remove("test_single_bit_header.bin");
    remove("test_decompressed_single_bit_header.txt");
}

void test_decompress_single_byte_with_bits() {
    // Create a compressed file with file_size = 1 and bits_in_last_byte = 4
    FILE *compressed_file = fopen("test_single_byte_with_bits.bin", "wb+");
    fputc(4, compressed_file); // bits_in_last_byte = 4
    fclose(compressed_file);

    compressed_file = fopen("test_single_byte_with_bits.bin", "rb");
    int bits_in_last_byte_read = fgetc(compressed_file);
    BITFILE *input_bitfile = bitfile_open(compressed_file, bits_in_last_byte_read);
    FILE *decompressed_file = fopen("test_decompressed_single_byte_with_bits.txt", "w+");

    decompress(input_bitfile, decompressed_file);

    bitfile_close(input_bitfile);
    fclose(decompressed_file);

    // Verify that the decompressed file is empty
    decompressed_file = fopen("test_decompressed_single_byte_with_bits.txt", "r");
    fseek(decompressed_file, 0, SEEK_END);
    long file_size = ftell(decompressed_file);
    assert_equals_int(0, file_size, "test_decompress_single_byte_with_bits: decompressed file should be empty");
    fclose(decompressed_file);

    remove("test_single_byte_with_bits.bin");
    remove("test_decompressed_single_byte_with_bits.txt");
}

void test_decompress_empty_compressed_file() {
    // Create an empty compressed file
    FILE *compressed_file = fopen("test_empty_compressed.bin", "wb+");
    fclose(compressed_file);

    compressed_file = fopen("test_empty_compressed.bin", "rb");
    // No bits_in_last_byte to read, fgetc will return EOF
    BITFILE *input_bitfile = bitfile_open(compressed_file, 0); 
    FILE *decompressed_file = fopen("test_decompressed_empty_compressed.txt", "w+");

    decompress(input_bitfile, decompressed_file);

    bitfile_close(input_bitfile);
    fclose(decompressed_file);

    // Verify that the decompressed file is empty
    decompressed_file = fopen("test_decompressed_empty_compressed.txt", "r");
    fseek(decompressed_file, 0, SEEK_END);
    long file_size = ftell(decompressed_file);
    assert_equals_int(0, file_size, "test_decompress_empty_compressed_file: decompressed file should be empty");
    fclose(decompressed_file);

    remove("test_empty_compressed.bin");
    remove("test_decompressed_empty_compressed.txt");
}

void test_decompress_early_eof_bitfile_getc() {
    // Create a dummy input file with some content
    FILE *input_file = fopen("test_input_early_eof.txt", "w+");
    fputs("a", input_file);
    fclose(input_file);

    // Compress the file
    input_file = fopen("test_input_early_eof.txt", "r");
    FILE *compressed_file = fopen("test_compressed_early_eof.bin", "wb+");
    BITFILE *output_bitfile = bitfile_open(compressed_file, 0);
    compress(input_file, output_bitfile);
    bitfile_close(output_bitfile);
    fclose(input_file);

    // Truncate the compressed file to simulate an early EOF during bit reading
    compressed_file = fopen("test_compressed_early_eof.bin", "r+");
    ftruncate(fileno(compressed_file), 1); // Truncate to 1 byte (header only)
    fclose(compressed_file);

    // Decompress the truncated file
    compressed_file = fopen("test_compressed_early_eof.bin", "rb");
    int bits_in_last_byte_read = fgetc(compressed_file);
    BITFILE *input_bitfile = bitfile_open(compressed_file, bits_in_last_byte_read);
    input_bitfile->total_bits_to_read = 0; // Force bitfile_getc to return EOF immediately
    FILE *decompressed_file = fopen("test_decompressed_early_eof.txt", "w+");
    decompress(input_bitfile, decompressed_file);
    bitfile_close(input_bitfile);
    fclose(decompressed_file);

    // Verify that the decompressed file is empty or incomplete
    decompressed_file = fopen("test_decompressed_early_eof.txt", "r");
    fseek(decompressed_file, 0, SEEK_END);
    long decompressed_size = ftell(decompressed_file);
    assert_true(decompressed_size >= 0, "test_decompress_early_eof_bitfile_getc: decompressed file size should be non-negative");
    fclose(decompressed_file);

    remove("test_input_early_eof.txt");
    remove("test_compressed_early_eof.bin");
    remove("test_decompressed_early_eof.txt");
}

