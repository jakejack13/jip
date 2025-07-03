#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "bitfile.h"
#include "utils.h"

void test_bitfile_putc_getc() {
    FILE *fp = fopen("test_bitfile.bin", "wb+");
    BITFILE *bf = bitfile_open(fp, 0);

    bitfile_putc(1, bf);
    bitfile_putc(0, bf);
    bitfile_putc(1, bf);
    bitfile_putc(1, bf);
    bitfile_putc(0, bf);
    bitfile_putc(0, bf);
    bitfile_putc(1, bf);
    bitfile_putc(0, bf);
    bitfile_sync(bf);

    bitfile_rewind(bf);

    assert_equals_int(bitfile_getc(bf), 1, "bitfile_putc_getc: first bit should be 1");
    assert_equals_int(bitfile_getc(bf), 0, "bitfile_putc_getc: second bit should be 0");
    assert_equals_int(bitfile_getc(bf), 1, "bitfile_putc_getc: third bit should be 1");
    assert_equals_int(bitfile_getc(bf), 1, "bitfile_putc_getc: fourth bit should be 1");
    assert_equals_int(bitfile_getc(bf), 0, "bitfile_putc_getc: fifth bit should be 0");
    assert_equals_int(bitfile_getc(bf), 0, "bitfile_putc_getc: sixth bit should be 0");
    assert_equals_int(bitfile_getc(bf), 1, "bitfile_putc_getc: seventh bit should be 1");
    assert_equals_int(bitfile_getc(bf), 0, "bitfile_putc_getc: eighth bit should be 0");

    bitfile_close(bf);
    fclose(fp);
    remove("test_bitfile.bin");
}

void test_bitfile() {
    test_bitfile_putc_getc();
}
