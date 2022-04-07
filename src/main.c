#include <stdio.h>
#include <string.h>

#include "compress.h"

#define USAGE "usage: jip -c/-d <origin> <destination>\n"

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
        compress(input, output);
    } else if (strcmp(argv[1], "-d") == 0) {
        decompress(input, output);
    } else {
        printf("jip: incorrect mode\n");
        printf(USAGE);
        return 1;
    }

    fclose(input);
    fclose(output);
}
