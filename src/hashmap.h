#ifndef __HT_H__
#define __HT_H__

#include "util/node.h"
#include "util/list.h"

#include <inttypes.h>

struct hashmap_t {
    list_t **hasharray;
    uint32_t size;
};

typedef struct hashmap_t hashmap_t;

hashmap_t *create_hashmap(uint32_t size);

void delete_hashmap(hashmap_t **hm);

void hashmap_insert(hashmap_t *hm, uint8_t *key, int value);

int hashmap_lookup(hashmap_t *hm, uint8_t *key);

#endif

