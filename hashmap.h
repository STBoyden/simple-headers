#pragma once

#include "sstring.h"
#include "types.h"
#include <stdlib.h>

typedef struct {
    void*   key;
    void*   value;
    size_t  size;
} HashMapEntry;

extern size_t HashMapEntry_calculate_size (Type, Type);

typedef struct {
    size_t          capacity;
    size_t          size;
    Type            key_type;
    Type            value_type;
    HashMapEntry*   buckets;
} HashMap;

extern void     HashMap_init        (HashMap*, Type, Type);
extern HashMap  HashMap_new         (Type, Type);
extern bool     HashMap_contains    (HashMap*, Type, void*);
extern bool     HashMap_insert      (HashMap*, Type, void*, Type, void*);
extern bool     HashMap_remove      (HashMap*, Type, void*);
extern void     HashMap_get         (HashMap*, Type, void*, void*);
extern void     HashMap_free        (HashMap*);
