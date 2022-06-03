#include "node.h"

#include <inttypes.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>

uint8_t *strdupl(char *str) {
    uint8_t *dup = calloc(strlen(str) + 1, sizeof(uint8_t));
    assert(dup);
    dup[strlen(str)] = '\0';
    strncpy((char *)dup, str, strlen(str));
    return dup;
}

node_t *create_node(uint8_t *key, int value) {
    node_t *n = (node_t *) malloc(sizeof(node_t));
    assert(n);
    char *k = (char *) key;
    n->key = strdupl(k);
    n->value = value;
    return n;
}

void delete_node(node_t **n) {
    if (n && *n) {
        if ((*n)->key)
            free((*n)->key);
        free(*n);
        *n = NULL;
    }
}

uint8_t *get_key(node_t *n) {
    if (n) {
        return n->key;
    }
    return NULL;
}

int get_val(node_t *n) {
    if (n) {
        return n->value;
    }
    return -1;
}

void set_value(node_t *n, int val) {
    if (n) {
        n->value = val;
    }
    return;
}

