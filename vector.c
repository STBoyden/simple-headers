#include "vector.h"
#include <stdio.h>

void Vector_init(Vector *vec, Type vec_type) {
    vec->len = 0;
    vec->blocks = 0;
    vec->type = vec_type;
    vec->arr = 0x0;
}

Vector Vector_new(Type vec_type) {
    Vector vec;
    Vector_init(&vec, vec_type);
    return vec;
}

bool Vector_push(Vector *vec, Type vec_type, void *data) {
    if (vec->type != vec_type) {
        return false;
    }

    if (vec->len >= vec->blocks) {
        vec->blocks = vec->blocks ? vec->blocks * 2 : 1;
        vec->arr = realloc(vec->arr, vec->blocks * Type_sizeof(vec->type));
    }

    vec->arr[vec->len++] = data;
    return true;
}

void *Vector_pop(Vector *vec) {
    if (!vec->len)
        return 0x0;

    void *v_ptr = vec->arr[--vec->len];
    if (vec->len <= vec->blocks / 2) {
        vec->blocks /= 2;
        vec->arr = realloc(vec->arr, vec->blocks * Type_sizeof(vec->type));
    }

    return v_ptr;
}

bool Vector_insert(Vector *vec, Type vec_type, void *data, size_t index) {
    if (vec->type != vec_type) {
        return false;
    }

    size_t amount = (vec->len - index) * Type_sizeof(vec->type);
    vec->len++;

    if (vec->len >= vec->blocks) {
        vec->blocks = vec->blocks ? vec->blocks * 2 : 1;
        vec->arr = realloc(vec->arr, vec->blocks * Type_sizeof(vec->type));
    }

    memmove(vec->arr + index + 1, vec->arr + index, amount);
    vec->arr[index] = data;

    return true;
}

void *Vector_remove(Vector* vec, size_t index) {
    size_t amount  = (vec->len - index - 1) * Type_sizeof(vec->type);

    void* data = vec->arr[index];
    vec->len--;
    memmove(vec->arr + index, vec->arr + index + 1, amount);

    if (vec->len <= vec->blocks / 2) {
        vec->blocks /= 2;
        vec->arr = realloc(vec->arr, vec->blocks * Type_sizeof(vec->type));
    }

    return data;
}

void Vector_free(Vector *vec) {
    free(vec->arr);
    vec->arr = 0x0;
    vec->blocks = 0;
    vec->len = 0;
    vec->type = TYPE_NULL;
}
