#include "sstring.h"
#include "types.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef K
#error dictionary.h: K not defined
#endif

#ifndef V
#error dictionary.h: V not defined
#endif

// GFG: Generic Name Generator
#define GNG3_(type0, type1, name) type0##_##type1##name
#define GNG3(type0, type1, name) GNG3_(type0, type1, name)

#define GNG_(type, name) type##name
#define GNG(type, name) GNG_(type, name)

typedef struct {
    K key;
    V value;
} GNG3(K, V, _entry);

static void GNG3(K, V, _entry_free)(GNG3(K, V, _entry) * entry) {
    GNG(K, _free)(&entry->key);
    GNG(V, _free)(&entry->value);
}

typedef struct {
    size_t seed0;
    size_t seed1;
    size_t capacity;
    size_t size;
    GNG3(K, V, _entry) * buckets;
} GNG3(K, V, _dict);

// T_K_dict_init - Initialises the given dict reference with default data.
static void GNG3(K, V, _dict_init)(GNG3(K, V, _dict) * dict) {
    dict->capacity = 1 << 4;
    dict->size = 0;
    dict->seed0 = 0;
    dict->seed1 = 0;
    dict->buckets = malloc(dict->capacity * sizeof(GNG3(K, V, _entry)));
}

// T_K_dict_new - Simply creates a new K_V_dict rather than forcing the use of
// K_V_dict_init and returns the K_V_dict.
static GNG3(K, V, _dict) GNG3(K, V, _dict_new)() {
    GNG3(K, V, _dict) dict;
    GNG3(K, V, _dict_init)(&dict);
    return dict;
}

// T_K_dict_new_with_capacity - Simply creates a new K_V_dict with a specified
// capacity rather than forcing the use of K_V_dict_init and returns the
// K_V_dict.
static GNG3(K, V, _dict) GNG3(K, V, _dict_new_with_capacity)(size_t capacity) {
    GNG3(K, V, _dict) dict;
    GNG3(K, V, _dict_init)(&dict);
    dict.capacity = capacity;
    return dict;
}

// T_K_dict_new_with_seeds - Simply creates a new K_V_dict with specified seeds
// rather than forcing the use of K_V_dict_init and returns the K_V_dict.
static GNG3(K, V, _dict)
    GNG3(K, V, _dict_new_with_seeds)(size_t seed0, size_t seed1) {
    GNG3(K, V, _dict) dict;
    GNG3(K, V, _dict_init)(&dict);
    dict.seed0 = seed0;
    dict.seed1 = seed1;
    return dict;
}

static GNG3(K, V, _entry)
    GNG3(K, V, _dict_insert)(GNG3(K, V, _dict) * dict, K key, V value) {
    GNG3(K, V, _entry) entry = {.key = key, .value = value};

    if (dict->size >= dict->capacity) {
        GNG3(K, V, _entry) *old = dict->buckets;
        size_t old_capacity = dict->capacity;

        dict->capacity = dict->capacity ? dict->capacity * 2 : 1;
        for (i32 i = 0; i < dict->size; i++) {
            GNG3(K, V, _entry_free)(&dict->buckets[i]);
        }
        free(dict->buckets);
        dict->buckets = (GNG3(K, V, _entry) *)malloc(
            dict->capacity * sizeof(GNG3(K, V, _entry)));

        GNG3(K, V, _entry) * e;
        while (e != NULL) {
            *e = old[GNG(K, _hash)(&key) % old_capacity];
            dict->buckets[GNG(K, _hash)(&e->key) % dict->capacity] = *e;
        }
    }

    dict->buckets[GNG(K, _hash)(&key) % dict->capacity] = entry;
    dict->size++;
    return entry;
}

static V *GNG3(K, V, _get)(GNG3(K, V, _dict) * dict, K key) {
    return &dict->buckets[GNG(K, _hash)(&key) % dict->capacity].value;
}

static void GNG3(K, V, _free)(GNG3(K, V, _dict) * dict) {
    for (i32 i = 0; i < dict->size; i++) {
        GNG3(K, V, _entry_free)(&dict->buckets[i]);
    }

    free(dict->buckets);
    dict->capacity = 1 << 4;
    dict->size = 0;
    dict->seed0 = 0;
    dict->seed1 = 0;
    dict->buckets = NULL;
}

#undef K
#undef V
#undef GNG
#undef GNG_
#undef GNG3
#undef GNG3_

