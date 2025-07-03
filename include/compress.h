#ifndef COMPRESS_H
#define COMPRESS_H

#include <stdio.h>

#include "bitfile.h"

#define EOF_CHAR (NUMCHARS - 1)

/** Compress the input file and store the information in the output file */
int compress(FILE *input, BITFILE *output);

/** Decompress the output file and store the information in the output file */
void decompress(BITFILE *input, FILE *output);

#endif //COMPRESS_H