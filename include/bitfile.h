/** bitfile.h
 * Bitwise reading and writing of files
 */

#ifndef BITFILE_H
#define BITFILE_H

#include <stdio.h>

/** A bit readable and writeable file */
typedef struct bitfile BITFILE;

struct bitfile {
    FILE *below;
    unsigned int bit;
    char curr_byte;
    int bits_in_last_byte;
    long total_bits_read;
    long total_bits_to_read;
};

/** Opens a new bitfile from the given file */
/** Opens a new bitfile from the given file */
BITFILE *bitfile_open(FILE *file, int bits_in_last_byte);

/** Closes the given bitfile */
void bitfile_close(BITFILE *file);

/** Gets the next bit from the file */
int bitfile_getc(BITFILE *file);

/** Puts a new bit into the file */
void bitfile_putc(char c, BITFILE *file);

/** Syncs the bitfile with the file below */
int bitfile_sync(BITFILE *file);

/** Rewinds the file back to the start */
void bitfile_rewind(BITFILE *file);

#endif  // BITFILE_H
