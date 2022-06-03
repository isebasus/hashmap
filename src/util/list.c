#include "list.h"

#include <stdio.h>
#include <assert.h>
#include <inttypes.h>
#include <stdlib.h>

listnode_t *new_node(void *x) {
    listnode_t *ln = (listnode_t *) malloc(sizeof(listnode_t));
    assert(ln);
    ln->next = NULL;
    ln->prev = NULL;
    ln->data = x;
    return ln;
}

void delete_listnode(listnode_t **ln) {
    if (ln && *ln) {
        free(*ln);
        *ln = NULL;
    }
}

list_t *create_list(void) {
    list_t *l = (list_t *) malloc(sizeof(list_t));
    assert(l);
    l->head = new_node(NULL);
    l->tail = new_node(NULL);
    l->head->next = l->tail;
    l->tail->prev = l->head;
    l->index = -1;
    l->elements = 0;
    return l;
}

void delete_list(list_t **l) {
    if (l && *l) {
        clear((*l));
        delete_listnode(&(*l)->head);
        delete_listnode(&(*l)->tail);
        free(*l);
        *l = NULL;
        return;
    }
    return;
}

int get_index(list_t *list) {
    if (!list)
        return -1;
    return list->index;
}

void append(list_t *list, void *x) {
    if (!list)
        return;
    listnode_t *n = new_node(x);
    n->next = list->tail;
    n->prev = list->tail->prev;
    list->tail->prev->next = n;
    list->tail->prev = n;
    list->curr = n;
    list->elements++;
}

void move_front(list_t *list) {
    if (!list || list->elements == 0)
        return;
    list->curr = list->head->next;
    list->index = list->elements != 0 ? 0 : -1;
}

void move_next(list_t *list) {
    if (!list)
        return;
    if (list->curr->next == list->tail) {
        list->index = -1;
        return;
    }
    list->curr = list->curr->next;
    list->index++;
}

void clear(list_t *list) {
    listnode_t *ln = list->head->next;
    while (ln->next != list->tail) {
        listnode_t *curr = ln;
        ln = ln->next;
        delete_listnode(&curr);
    }
    list->index = -1;
    list->elements = 0;
}

void *get(list_t *list) {
    if (!list)
        return NULL;
    return list->curr->data;
}
