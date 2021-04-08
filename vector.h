#pragma once

#include <stdlib.h>
#include "types.h"

typedef struct {
    size_t  len;
    size_t  blocks;
    Type    type;
    void**  arr;
} Vector;

extern void     Vector_init     (Vector *, Type);
extern Vector   Vector_new      (Type);
extern bool     Vector_push     (Vector *, Type, void*);
extern void*    Vector_pop      (Vector *);
extern bool     Vector_insert   (Vector *, Type, void*, size_t);
extern void*    Vector_remove   (Vector *, size_t);
extern void     Vector_free     (Vector *);
