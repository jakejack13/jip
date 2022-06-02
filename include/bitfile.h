/** bitfile.h
 * Bitwise reading and writing of files
 */

#ifndef BITFILE_H
#define BITFILE_H

#include <stdio.h>

/** A bit readable and writeable file */
typedef struct bitfile BITFILE;

/** Opens a new bitfile from the given file */
BITFILE *bitfile_open(FILE *file);

/** Closes the given bitfile */
void bitfile_close(BITFILE *file);

/** Gets the next bit from the file */
char bitfile_getc(BITFILE *file);

/** Puts a new bit into the file */
void bitfile_putc(char c, BITFILE *file);

/** Syncs the bitfile with the file below */
void bitfile_sync(BITFILE *file);

/** Rewinds the file back to the start */
void bitfile_rewind(BITFILE *file);

#endif //BITFILE_H
