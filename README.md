# 🗺️ hashmap 

A funny, basic hashmap written in C.

# Documentation

The hashmap is created dynamically using `create_hashmap()` and freed using
`delete_hashmap()`.

```c
hashmap_t *create_hashmap(uint32_t size);

void delete_hashmap(hashmap_t **hm);
```

To insert unique elements, we can use `hashmap_insert()` and
to look up elements, we can use `hashmap_lookup`.

```c
void hashmap_insert(hashmap_t *hm, uint8_t *key, int value);

int hashmap_lookup(hashmap_t *hm, uint8_t *key);
```