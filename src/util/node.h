#ifndef _NODE_H_
#define _NODE_H_

#include <stdio.h>
#include <inttypes.h>

typedef struct node_t node_t;

struct node_t {
    uint8_t *key;
    int value;
    node_t *next;
    node_t *prev;
};

node_t *create_node(uint8_t *key, int value);

void delete_node(node_t **n);

uint8_t *strdupl(char *str);

uint8_t *get_key(node_t *n);

int get_val(node_t *n);

void set_value(node_t *n, int val);

#endif 
