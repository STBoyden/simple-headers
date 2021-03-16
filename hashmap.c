#include "hashmap.h"
#include <string.h>
#include <stdio.h>

#define _STR(x) #x
#define STR(x) _STR(x)

void HashMap_init(HashMap *hm, Type key_type, Type value_type) {
    hm->capacity = 1 << 4;
    hm->size = 0;
    hm->buckets = malloc(hm->capacity * sizeof(HashMapEntry));
    hm->key_type = key_type;
    hm->value_type = value_type;
}

HashMap HashMap_new(Type key_type, Type value_type) {
    HashMap hm;
    HashMap_init(&hm, key_type, value_type);
    return hm;
}

bool HashMap_contains(HashMap *hm, Type key_type, void *key) {
    if (hm->key_type != key_type) {
        fprintf(stderr, "HashMap_contains: HashMap has key_type of " STR(hm->key_type)
                        " but was instead supplied with key of type " STR(key_type));
        return false;
    }

    for (i32 i = 0; i < hm->size; i++) {
        if (Type_hash(key_type, key) == Type_hash(key_type, hm->buckets[i].key)) {
            return true;
        }
    }

    return false;
}

bool HashMap_insert(HashMap *hm, Type key_type, void *key, Type value_type, void *value) {
    HashMapEntry entry = {.key = key, .value = value};
    if (hm->key_type != key_type) {
        fprintf(stderr, "HashMap_insert: HashMap has key_type of " STR(hm->key_type)
                        " but was instead supplied with key of type " STR(key_type));
        return false;
    }

    if (hm->value_type != value_type) {
        fprintf(stderr, "HashMap_insert: HashMap has value_type of " STR(hm->value_type)
                        " but was instead supplied with value of type " STR(value_type));
        return false;
    }

    if (HashMap_contains(hm, key_type, key)) {
        return false;
    }

    if (hm->size >= hm->capacity) {
        HashMapEntry *old = hm->buckets;
        size_t old_capacity = hm->capacity;

        hm->capacity = hm->capacity ? hm->capacity * 2 : 1;

        free(hm->buckets);
        hm->buckets = (HashMapEntry *) malloc(hm->capacity * sizeof(HashMapEntry));

        HashMapEntry *e = NULL;
        while (e != NULL) {
            *e = old[Type_hash(key_type, key) % old_capacity];
            hm->buckets[Type_hash(key_type, key) % hm->capacity] = *e;
        }

#ifdef DEBUG
        printf("HashMap grown");
#endif
    }

    hm->buckets[Type_hash(key_type, key) % hm->capacity] = entry;
    hm->size++;

    return true;
}

bool HashMap_remove(HashMap *hm, Type key_type, void *key) {
    if (hm->key_type != key_type) {
        fprintf(stderr, "HashMap_remove: HashMap has key_type of " STR(hm->key_type)
                        " but was instead supplied with key of type " STR(key_type));
        return false;
    }

    if (!HashMap_contains(hm, key_type, key))
        return false;

    free(&hm->buckets[Type_hash(key_type, key) % hm->capacity]);
    hm->size--;

    if (hm->size <= hm->capacity / 2) {
        HashMapEntry *old = hm->buckets;
        size_t old_capacity = hm->capacity;
        hm->capacity /= 2;
        free(hm->buckets);
        hm->buckets = (HashMapEntry *) malloc(hm->capacity * sizeof(HashMapEntry));

        HashMapEntry *e = NULL;
        while (e != NULL) {
            *e = old[Type_hash(key_type, key) % old_capacity];
            hm->buckets[Type_hash(key_type, key) % hm->capacity] = *e;
        }

#ifdef DEBUG
        printf("HashMap shrunk");
#endif
    }

    return true;
}

void *HashMap_get(HashMap *hm, Type key_type, void *key) {
    if (hm->key_type != key_type) {
        fprintf(stderr, "HashMap_remove: HashMap has key_type of " STR(hm->key_type)
                        " but was instead supplied with key of type " STR(key_type));
        return NULL;
    }

    if (!HashMap_contains(hm, key_type, key))
        return NULL;

    return &hm->buckets[Type_hash(key_type, key) % hm->capacity];
}

void HashMap_free(HashMap *hm) {
    free(hm->buckets);
    hm->capacity = 1 << 4;
    hm->size = 0;
    hm->buckets = NULL;
}
