#include <stdlib.h>
#include <stdio.h>
#include <limits.h> // For LONG_MAX

#include "bitfile.h"



static void bitfile_update_read_length(BITFILE *file) {
    long current_pos = ftell(file->below);
    fseek(file->below, 0, SEEK_END);
    long file_size = ftell(file->below);
    fseek(file->below, current_pos, SEEK_SET);

    if (file_size == 0) {
        file->total_bits_to_read = 0;
    } else {
        file->total_bits_to_read = (file_size - 1) * 8 + file->bits_in_last_byte;
    }
}

BITFILE *bitfile_open(FILE *file, int bits_in_last_byte) {
    BITFILE *bitfile = malloc(sizeof(struct bitfile));
    bitfile->below = file;
    bitfile->bit = 0;
    bitfile->curr_byte = 0; // Initialize curr_byte
    bitfile->bits_in_last_byte = bits_in_last_byte; // Initialize new field
    bitfile->total_bits_read = 0;

    bitfile_update_read_length(bitfile);

    return bitfile;
}

void bitfile_close(BITFILE *file) {
    free(file);
}

int bitfile_getc(BITFILE *file) {
    if (file->total_bits_read >= file->total_bits_to_read) {
        return EOF;
    }

    if(file->bit == 0) {
        int c = fgetc(file->below);
        if (c == EOF) {
            return EOF; // Should not happen if total_bits_to_read is correct
        }
        file->curr_byte = (char)c;
    }
    char result = (file->curr_byte >> (7 - file->bit)) & 1;
    file->bit = (file->bit+1) % 8;
    file->total_bits_read++;
    return result;
}

void bitfile_putc(char c, BITFILE *file) {
    file->curr_byte = (file->curr_byte << 1) | (c & 1);
    file->bit++;
    if (file->bit == 8) {
        fputc(file->curr_byte, file->below);
        file->curr_byte = 0;
        file->bit = 0;
    }
}

int bitfile_sync(BITFILE *file) {
    int bits_to_write;
    if (file->bit != 0) {
        file->curr_byte <<= (8 - file->bit);
        fputc(file->curr_byte, file->below);
        bits_to_write = file->bit;
    } else {
        bits_to_write = 8;
    }
    fflush(file->below);
    return bits_to_write;
}

void bitfile_rewind(BITFILE *file) {
    rewind(file->below);
    file->bit = 0;
    file->curr_byte = 0;
    file->total_bits_read = 0;
    bitfile_update_read_length(file);
}
