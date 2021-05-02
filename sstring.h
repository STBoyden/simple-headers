#pragma once

#include <stdio.h>

// a wrapper over a char_vec to implement a simple heap allocated string type


#include "vector.h"

typedef struct {
    Vector data;
    size_t *len;
} String;

#include "types.h"

static String String_new(str s) {
    String str;
    str.data = Vector_new(TYPE_STR);
    str.len = &str.data.len;

    for (i32 i = 0; i < strlen(s); i++) {
        Vector_push(&str.data, TYPE_STR, &s[i]);
    }

    return str;
}

static char String_push(String *string_ref, char c) {
    if (Vector_push(&string_ref->data, TYPE_STR, &c)) {
        return c;
    } else {
        fprintf(stderr, "Failed to push character %c onto end of string", c);
        return c;
    }
}

static char String_pop(String *string_ref) {
    return *(char*)Vector_pop(&string_ref->data);
}

static char String_insert(String *string_ref, char c, size_t index) {
    if (Vector_insert(&string_ref->data, TYPE_STR, &c, index)) {
        return c;
    } else {
        fprintf(stderr, "Failed to insert character %c into position %ld", c, index);
        return c;
    }
}

static str String_to_cstr(String *string_ref) {
    str cstr = (str) malloc((string_ref->data.len + 1 * sizeof(char)));

    for (i32 i = 0; i < string_ref->data.len; i++) {
        cstr[i] = *(char*)string_ref->data.arr[i];
    }

    return cstr;
}

static void String_free(String *string_ref) {
    Vector_free(&string_ref->data);
}

static size_t String_length(String *string_ref) { return *string_ref->len; }
