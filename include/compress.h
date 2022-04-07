#ifndef COMPRESS_H
#define COMPRESS_H

#include <stdio.h>

/** Compress the input file and store the information in the output file */
void compress(FILE *input, FILE *output);

/** Decompress the output file and store the information in the output file */
void decompress(FILE *input, FILE *output);

#endif //COMPRESS_H