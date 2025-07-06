#include <stdio.h>
#include <string.h>

#include "bitfile.h"
#include "compress.h"

#define USAGE "usage: jip -c/-d <origin> <destination>\n"

/** The main entrypoint for the program */
int main(int argc, char *argv[]) {
    if (argc < 4) {
        printf("jip: too few arguments\n");
        printf(USAGE);
        return 1;
    }

    FILE *input = fopen(argv[2], "r");
    FILE *output = fopen(argv[3], "w+");
    if (input == NULL || output == NULL) {
        printf("jip: could not open file\n");
        printf(USAGE);
        return 1;
    }

    if (strcmp(argv[1], "-c") == 0) {
        BITFILE *output_bit = bitfile_open(output, 0);
        compress(input, output_bit);
        bitfile_close(output_bit);
    } else if (strcmp(argv[1], "-d") == 0) {
        BITFILE *input_bit = bitfile_open(input, 0);
        decompress(input_bit, output);
        bitfile_close(input_bit);
    } else {
        printf("jip: incorrect mode\n");
        printf(USAGE);
        return 1;
    }

    fclose(input);
    fclose(output);

    return 0;
}
