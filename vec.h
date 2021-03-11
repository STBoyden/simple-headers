// implementation of a vector, shamelessly stolen from aosync's greenthread
// library: https://github.com/aosync/gthr.

#include <stdlib.h>
#include <string.h>

#ifndef T
#error vec.h: T not defined
#endif

#define GNG_(type, name) type##name
#define GNG(type, name) GNG_(type, name)

typedef struct {
    size_t len;
    size_t blocks;
    T *arr;
} GNG(T, _vec);

// T_vec_init - Initialises the given vector reference with default data.
static void GNG(T, _vec_init)(GNG(T, _vec) *vec) {
    vec->len = 0;
    vec->blocks = 0;
    vec->arr = NULL;
}

// T_vec_new - Simply creates a new T_vec rather than forcing the use of
// T_vec_init and returns the T_vec.
GNG(T, _vec) GNG(T, _vec_new)() {
    GNG(T, _vec) vec;
    GNG(T, _vec_init)(&vec);
    return vec;
}

// T_vec_push - Pushes t to the end of the T_vec and returns the value t.
static T GNG(T, _vec_push)(GNG(T, _vec) *vec, T t) {
    if (vec->len >= vec->blocks) {
        vec->blocks = vec->blocks ? vec->blocks * 2 : 1;
        vec->arr = (T *) realloc(vec->arr, vec->blocks * sizeof(T));
    }

    vec->arr[vec->len++] = t;
    return t;
}

// T_vec_pop - Pops the last element of the T_vec and returns the value.
static T GNG(T, _vec_pop)(GNG(T, _vec) *vec) {
    T t;
    if (vec->len == 0)
        return t;
    t = vec->arr[--vec->len];
    if (vec->len <= vec->blocks / 2) {
        vec->blocks /= 2;
        vec->arr = (T *) realloc(vec->arr, vec->blocks * sizeof(T));
    }

    return t;
}

// T_vec_insert - Inserts t at the given index and returns the inserted value.
static T GNG(T, _vec_insert)(GNG(T, _vec) *vec, size_t index, T t) {
    size_t amount = (vec->len - index) * sizeof(T);
    vec->len++;
    if (vec->len >= vec->blocks) {
        vec->blocks = vec->blocks ? vec->blocks * 2 : 1;
        vec->arr = (T *) realloc(vec->arr, vec->blocks * sizeof(T));
    }
    memmove(vec->arr + index + 1, vec->arr + index, amount);
    vec->arr[index] = t;

    return t;
}

// T_vec_remove - Removes a T at the given index and returns the value.
static T GNG(T, _vec_remove)(GNG(T, _vec) *vec, size_t index) {
    size_t amount = (vec->len - index - 1) * sizeof(T);
    T what = vec->arr[index];
    vec->len--;
    memmove(vec->arr + index, vec->arr + index + 1, amount);
    if (vec->len <= vec->blocks / 2) {
        vec->blocks /= 2;
        vec->arr = (T *) realloc(vec->arr, vec->blocks * sizeof(T));
    }
    return what;
}

// T_vec_free - Frees the T_vec's memory.
static void GNG(T, _vec_free)(GNG(T, _vec) *vec) {
    free(vec->arr);
    vec->arr = NULL;
    vec->blocks = 0;
    vec->len = 0;
}

#undef T
#undef GNG
#undef GNG_
