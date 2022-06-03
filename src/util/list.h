#ifndef _LIST_H_
#define _LIST_H_

#include <inttypes.h>

typedef struct listnode_t listnode_t;

struct listnode_t {
    listnode_t *next;
    listnode_t *prev;
    void *data;
};

struct list_t {
    listnode_t *head;
    listnode_t *tail;
    listnode_t *curr;
    uint32_t elements;
    uint32_t index;
};

typedef struct list_t list_t;

list_t *create_list(void);

void delete_list(list_t **l);

int get_index(list_t *list);

void append(list_t *list, void *x);

void move_front(list_t *list);

void move_next(list_t *list);

void clear(list_t *list);

void *get(list_t *list);

#endif 
