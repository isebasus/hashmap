#include "hashmap/hashmap.h"
#include "hashmap/util/node.h"

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <string.h>
#include <assert.h>

// ACCESS FUNCTIONS TESTS

#define MAP_SIZE 10000

int test_hashmap_lookup() {
    hashmap_t *table = create_hashmap(MAP_SIZE);

    uint8_t buf[10] = { 0 };
    for (int i = 0; i < MAP_SIZE; i++) {
        // Insert into hashmap
        fprintf(stdout, "Inserting: %i\n", i);
        sprintf((char *) buf, "%i", i);
		uint8_t *key = strdupl((char *) buf);
	    hashmap_insert(table, key, i);
        free(key);
    }

    int val;
    for (int i = 0; i < MAP_SIZE; i++) {
        sprintf((char *) buf, "%i", i);
        uint8_t *key = strdupl((char *) buf);
        if ((val = hashmap_lookup(table, key)) != -1) {
            fprintf(stdout, "key: %s, value: %i\n", key, val);
        } else {
            delete_hashmap(&table);
            free(key);
            return 1;
        }
        free(key);
    }
    delete_hashmap(&table);
    return 0;
}

static inline void results(int (*f)(), char *test) {
    if (f() >= 1) {
        printf("%s: FAILED TEST %d\n", test, f());
        return;
    }
    printf("%s: PASSED TEST\n", test);
}

int main(){
    printf("TESTING ACCESS FUNCTIONS\n");
    printf("--------------------------------------------------------------\n");
    results(test_hashmap_lookup, "Hashmap Lookup Test");
    printf("--------------------------------------------------------------\n");
    return(0);
}
