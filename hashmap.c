#include "hashmap.h"

#include <stdio.h>
#include <string.h>

#define _STR(x) #x
#define STR(x) _STR(x)

size_t HashMapEntry_calculate_size(Type key_type, Type value_type) {
    return Type_sizeof(key_type) + Type_sizeof(value_type);
}

void HashMap_init(HashMap* hm, Type key_type, Type value_type) {
    hm->capacity = 1 << 4;
    hm->size = 0;
    hm->buckets = malloc(
        hm->capacity * HashMapEntry_calculate_size(key_type, value_type)
    );
    hm->key_type = key_type;
    hm->value_type = value_type;
}

HashMap HashMap_new(Type key_type, Type value_type) {
    HashMap hm;
    HashMap_init(&hm, key_type, value_type);
    return hm;
}

bool HashMap_contains(HashMap* hm, Type key_type, void* key) {
    if (hm->key_type != key_type) {
        fprintf(
            stderr,
            "HashMap_contains: HashMap has key_type of " STR(hm->key_type)
            " but was instead supplied with key of type " STR(key_type)
        );
        return false;
    }


    u64 key_hash = Type_hash(key_type, key);

    if (!&hm->buckets[key_hash % hm->capacity]) {
        return false;
    }

    if (key_hash == Type_hash(key_type, hm->buckets[key_hash % hm->capacity].key)) {
        return true;
    }

    return false;
}

bool HashMap_insert(
    HashMap*    hm,
    Type        key_type,
    void*       key,
    Type        value_type,
    void*       value
) {
    HashMapEntry entry = { .key = key, .value = value };
    if (hm->key_type != key_type) {
        fprintf(
            stderr,
            "HashMap_insert: HashMap has key_type of " STR(hm->key_type)
            " but was instead supplied with key of type " STR(key_type)
        );
        return false;
    }

    if (hm->value_type != value_type) {
        fprintf(
            stderr,
            "HashMap_insert: HashMap has value_type of " STR(hm->value_type)
            " but was instead supplied with value of type " STR(value_type)
        );
        return false;
    }

    if (HashMap_contains(hm, key_type, key)) {
        return false;
    }

    u64 key_hash = Type_hash(key_type, key);

    if (hm->size >= hm->capacity) {
        HashMapEntry* old = hm->buckets;
        size_t old_capacity = hm->capacity;

        hm->capacity = hm->capacity ? hm->capacity * 2 : 1;

        free(hm->buckets);
        hm->buckets = (HashMapEntry*) malloc(
            hm->capacity * HashMapEntry_calculate_size(hm->key_type, hm->value_type)
        );

        HashMapEntry* e = 0;
        while (e) {
            *e = old[key_hash % old_capacity];
            hm->buckets[key_hash % hm->capacity] = *e;
        }

#ifdef DEBUG
        printf("DEBUG: HashMap_insert: HashMap grown\n");
#endif
    }

    hm->buckets[key_hash % hm->capacity] = entry;
    hm->size++;

    return true;
}

bool HashMap_remove(HashMap* hm, Type key_type, void* key) {
    if (hm->key_type != key_type) {
        fprintf(
            stderr,
            "HashMap_remove: HashMap has key_type of " STR(hm->key_type)
            " but was instead supplied with key of type " STR(key_type)
        );
        return false;
    }

    if (!HashMap_contains(hm, key_type, key))
        return false;

    u64 key_hash = Type_hash(key_type, key);

    hm->size--;

#ifdef DEBUG
    printf(
        "DEBUG: HashMap_remove: hashmap size: %d, hashmap capacity: %d\n",
        hm->size,
        hm->capacity
    );
#endif

    if (hm->size <= hm->capacity / 2) {
        HashMapEntry* old = hm->buckets;
        size_t old_capacity = hm->capacity;
        hm->capacity /= 2;
        hm->buckets = (HashMapEntry*)malloc(
            hm->capacity * HashMapEntry_calculate_size(hm->key_type, hm->value_type)
        );

        HashMapEntry* e = 0x0;
        while (e != 0x0) {
            *e = old[key_hash % old_capacity];
            hm->buckets[key_hash % hm->capacity] = *e;
        }

#ifdef DEBUG
        printf("DEBUG: HashMap_remove: HashMap shrunk\n");
#endif
    }

    return true;
}

void HashMap_get(HashMap* hm, Type key_type, void* key, void* out) {
    if (hm->key_type != key_type) {
        fprintf(
            stderr,
            "HashMap_remove: HashMap has key_type of " STR(hm->key_type)
            " but was instead supplied with key of type " STR(key_type)
        );
        out = 0x0;
    }

    if (!HashMap_contains(hm, key_type, key)) {
        fprintf(stderr, "Given hashmap does not contain supplied key");
        out = 0x0;
    }

    out = &hm->buckets[Type_hash(key_type, key) % hm->capacity].value;
}

void HashMap_free(HashMap* hm) {
    free(hm->buckets);
    hm->capacity = 1 << 4;
    hm->size = 0;
    hm->buckets = 0x0;
}
