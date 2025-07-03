#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "huffman.h"
#include "bitfile.h"
#include "utils.h"

void test_huffman_init() {
    huffman_t *h = huffman_init('a', 10);
    assert_true(h != NULL, "huffman_init: should not return NULL");
    assert_equals_int(huffman_get_frequency(h), 10, "huffman_init: frequency should be 10");
    huffman_free(h);
}

void test_huffman_add_left_right() {
    huffman_t *root = huffman_init(-1, 20);
    huffman_t *left = huffman_init('a', 10);
    huffman_t *right = huffman_init('b', 10);

    huffman_add_left(root, left);
    huffman_add_right(root, right);

    assert_true(root != NULL, "huffman_add_left_right: root should not be NULL");
    assert_true(left != NULL, "huffman_add_left_right: left should not be NULL");
    assert_true(right != NULL, "huffman_add_left_right: right should not be NULL");

    huffman_free(root);
}

void test_huffman_get_code() {
    huffman_t *root = huffman_init(-1, 20);
    huffman_t *left = huffman_init('a', 10);
    huffman_t *right = huffman_init('b', 10);

    huffman_add_left(root, left);
    huffman_add_right(root, right);

    huffman_assign_codes(root);

    assert_equals_int(huffman_get_code(root, 'a'), 0, "huffman_get_code: code for 'a' should be 0");
    assert_equals_int(huffman_get_code_length(root, 'a'), 1, "huffman_get_code: length for 'a' should be 1");
    assert_equals_int(huffman_get_code(root, 'b'), 1, "huffman_get_code: code for 'b' should be 1");
    assert_equals_int(huffman_get_code_length(root, 'b'), 1, "huffman_get_code: length for 'b' should be 1");

    huffman_free(root);
}

void test_huffman_save_load() {
    huffman_t *root = huffman_init(-1, 20);
    huffman_t *left = huffman_init('a', 10);
    huffman_t *right = huffman_init('b', 10);

    huffman_add_left(root, left);
    huffman_add_right(root, right);

    FILE *fp = fopen("test_huffman.bin", "wb+");
    BITFILE *bf = bitfile_open(fp, 0);
    huffman_save_to_file(root, bf);
    bitfile_sync(bf);
    bitfile_rewind(bf);

    huffman_t *loaded_root = huffman_load_from_file(bf);

    // This is a basic check. A more robust test would compare the structure and values of the trees.
    assert_true(loaded_root != NULL, "huffman_save_load: loaded root should not be NULL");
    assert_true(loaded_root->left != NULL, "huffman_save_load: loaded left should not be NULL");
    assert_true(loaded_root->right != NULL, "huffman_save_load: loaded right should not be NULL");

    bitfile_close(bf);
    fclose(fp);
    remove("test_huffman.bin");
    huffman_free(root);
    huffman_free(loaded_root);
}

void test_huffman() {
    test_huffman_init();
    test_huffman_add_left_right();
    test_huffman_get_code();
    test_huffman_save_load();
}
