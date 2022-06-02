#include <stdlib.h>

#include "bitfile.h"

struct bitfile {
    FILE *below;
    unsigned int bit;
    char curr_byte;
};

BITFILE *bitfile_open(FILE *file) {
    BITFILE *bitfile = malloc(sizeof(struct bitfile));
    bitfile->below = file;
    bitfile->bit = 0;
    return bitfile;
}

void bitfile_close(BITFILE *file) {
    free(file);
}

char bitfile_getc(BITFILE *file) {
    if(file->bit == 0) file->curr_byte = fgetc(file->below);
    char result = (file->curr_byte >> (7 - file->bit)) & 1;
    file->bit = (file->bit+1) % 8;
    return result;
}

void bitfile_putc(char c, BITFILE *file) {
    if (file->bit == 0) {
        fputc(file->curr_byte, file->below);
        file->curr_byte = 0;
    } else {
        file->curr_byte = file->curr_byte << 1;
    }
    file->curr_byte += c;
    file->bit = (file->bit+1) % 8;
}

void bitfile_sync(BITFILE *file) {
    fputc(file->curr_byte, file->below);
}

void bitfile_rewind(BITFILE *file) {
    rewind(file->below);
}
