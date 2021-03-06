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

// K_V_entry_free - Frees the entry and it's contents.
static void GNG3(K, V, _entry_free)(GNG3(K, V, _entry) *entry) {
    GNG(K, _free)(&entry->key);
    GNG(V, _free)(&entry->value);
}

typedef struct {
    size_t capacity;
    size_t size;
    GNG3(K, V, _entry) *buckets;
} GNG3(K, V, _dict);

// K_V_dict_init - Initialises the given dict reference with default data.
static void GNG3(K, V, _dict_init)(GNG3(K, V, _dict) *dict) {
    dict->capacity = 1 << 4;
    dict->size = 0;
    dict->buckets = malloc(dict->capacity * sizeof(GNG3(K, V, _entry)));
}

// K_V_dict_new - Simply creates a new K_V_dict rather than forcing the use of
// K_V_dict_init and returns the K_V_dict.
static GNG3(K, V, _dict) GNG3(K, V, _dict_new)() {
    GNG3(K, V, _dict) dict;
    GNG3(K, V, _dict_init)(&dict);
    return dict;
}

// K_V_dict_new_with_capacity - Simply creates a new K_V_dict with a specified
// capacity rather than forcing the use of K_V_dict_init and returns the
// K_V_dict.
static GNG3(K, V, _dict) GNG3(K, V, _dict_new_with_capacity)(size_t capacity) {
    GNG3(K, V, _dict) dict;
    GNG3(K, V, _dict_init)(&dict);
    dict.capacity = capacity;
    return dict;
}

// K_V_dict_contains - Returns true or false on whether the supplied dictionary
// contains the supplied key.
static bool GNG3(K, V, _dict_contains)(GNG3(K, V, _dict) *dict, K key) {
    for (i32 i = 0; i < dict->size; i++) {
        if (GNG(K, _hash)(&key) == GNG(K, _hash)(&dict->buckets[i].key)) {
            return true;
        }
    }

    return false;
}

// K_V_dict_insert - Inserts the given key and value into the supplied dictionary and
// returns the entry that is generated.
static GNG3(K, V, _entry)
GNG3(K, V, _dict_insert)(GNG3(K, V, _dict) *dict, K key, V value) {
    GNG3(K, V, _entry) entry = {.key = key, .value = value};

    if (GNG3(K, V, _dict_contains)(dict, key)) {
        fprintf(stderr, "Key already exists in this dictionary\n");
        return entry;
    }

    if (dict->size >= dict->capacity) {
        GNG3(K, V, _entry) *old = dict->buckets;
        size_t old_capacity = dict->capacity;

        dict->capacity = dict->capacity ? dict->capacity * 2 : 1;
        for (i32 i = 0; i < dict->size; i++) {
            GNG3(K, V, _entry_free)(&dict->buckets[i]);
        }
        free(dict->buckets);
        dict->buckets = (GNG3(K, V, _entry) *) malloc(
                dict->capacity * sizeof(GNG3(K, V, _entry)));

        GNG3(K, V, _entry) *e = NULL;
        while (e != NULL) {
            *e = old[GNG(K, _hash)(&key) % old_capacity];
            dict->buckets[GNG(K, _hash)(&e->key) % dict->capacity] = *e;
        }
    }

    dict->buckets[GNG(K, _hash)(&key) % dict->capacity] = entry;
    dict->size++;
    return entry;
}

// K_V_dict_remove - Removes an entry from the supplied dict by key, then returns the
// entry that was removed.
static GNG3(K, V, _entry)
GNG3(K, V, _dict_remove)(GNG3(K, V, _dict) *dict, K key) {
    GNG3(K, V, _entry) entry = dict->buckets[GNG(K, _hash)(&key) % dict->capacity];
    GNG3(K, V, _entry_free)(&dict->buckets[GNG(K, _hash)(&key) % dict->capacity]);

    // TODO: shrink buckets array if necessary

    dict->size--;
    return entry;
}

// K_V_dict_get - Gets a value associated with the supplied key in the supplied dict.
static V GNG3(K, V, _dict_get)(GNG3(K, V, _dict) *dict, K key) {
    if (GNG3(K, V, _dict_contains)(dict, key)) {
        fprintf(stderr, "Key does not exist in dictionary\n");
        // TODO: custom error type
    }

    return dict->buckets[GNG(K, _hash)(&key) % dict->capacity].value;
}

// K_V_dict_free - Frees the supplied dict and all it's entries.
static void GNG3(K, V, _dict_free)(GNG3(K, V, _dict) *dict) {
    for (i32 i = 0; i < dict->size; i++) {
        GNG3(K, V, _entry_free)(&dict->buckets[i]);
    }

    free(dict->buckets);
    dict->capacity = 1 << 4;
    dict->size = 0;
    dict->buckets = NULL;
}

#undef K
#undef V
#undef GNG
#undef GNG_
#undef GNG3
#undef GNG3_
