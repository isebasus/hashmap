#include "hashmap.h"
#include "util/node.h"
#include "util/list.h"

#include <inttypes.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>

// Constructor/Destructors ----------------------------------------------

hashmap_t *create_hashmap(uint32_t size) {
    hashmap_t *h = (hashmap_t *) malloc(sizeof(hashmap_t));
    assert(h);
    h->size = size;
    h->hasharray = calloc(size, sizeof(list_t *));
    return h;
}

void delete_hashmap(hashmap_t **hm) {
    if (hm && *hm) {
        for (uint32_t i = 0; i < (*hm)->size; i++) {
            if ((*hm)->hasharray[i] != NULL) {
                list_t *list = (*hm)->hasharray[i];
                for (move_next(list); get_index(list) >= 0; move_next(list)) {
                    node_t *node = (node_t *) get(list);
                    delete_node(&node);
                }
                delete_list(&list);
            }
        }
        free((*hm)->hasharray);
        free(*hm);
        *hm = NULL;
    }
    return;
}

// Private Functions ---------------------------------------------------

/*
*   hash()
*   
*   This function is used to hash strings to get the index for 
*   the hasharray
*/
uint32_t hash(uint8_t *key, uint32_t size)
{
    uint32_t hash, i;
    for(hash = i = 0; i < size; ++i)
    {
        hash += key[i];
        hash += (hash << 10);
        hash ^= (hash >> 6);
    }
    hash += (hash << 3);
    hash ^= (hash >> 11);
    hash += (hash << 15);
    return hash;
}

/*
*   list_lookup()
*   
*   This is used by hashmap_insert and hashmap_lookup to find 
*   any nodes that have collided
*/
node_t *list_lookup(list_t *list, uint8_t *key) {
    if (list) {
        for (move_front(list); get_index(list) >= 0; move_next(list)) {
            node_t *node = (node_t *) get(list);
            if (strcmp((char *)get_key(node), (char *)key) == 0) {
                return node;
            }
        }
    }
    return NULL;
}

// Public Functuions ---------------------------------------------------

/*
*   hashmap_insert()
*   
*   Here we can pretend that the client does not add duplicated
*   data, and uses hashmap_lookup before inserting
*/
void hashmap_insert(hashmap_t *hm, uint8_t *key, int value) {
    uint32_t index = hash(key, strlen((char *) key));
    list_t *l = hm->hasharray[index % hm->size];
    if (l == NULL) {
        l = create_list();
        hm->hasharray[index % hm->size] = l;
    }
    // If there is a node collision, then just set the node
    node_t *node = list_lookup(l, key);
    if (node == NULL) {
        node_t *node = create_node(key, value);
        append(l, node);
        return;
    }
    set_value(node, value);
}

/*
*   hashmap_lookup()
*   
*   This is used for the client to see if a key
*   already exists within a hashmaps
*/
int hashmap_lookup(hashmap_t *hm, uint8_t *key) {
    uint32_t index = hash(key, strlen((char *) key));
    list_t *l = hm->hasharray[index % hm->size];
    return get_val(list_lookup(l, key));
}
