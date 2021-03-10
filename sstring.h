#pragma once

#include <stdio.h>

// a wrapper over a char_vec to implement a simple heap allocated string type

#include "types.h"

#define T char
#include "vec.h"

typedef struct string string;

struct string {
    char_vec data;
};

static string string_new(const str s) {
    string str;
    str.data = char_vec_new();

    for (i32 i = 0; i < strlen(s); i++) {
        char_vec_push(&str.data, s[i]);
    }

    return str;
}

static char string_push(string *str, char c) {
    return char_vec_push(&str->data, c);
}

static char string_pop(string *str) { return char_vec_pop(&str->data); }

static char string_insert(string *str, char c, size_t index) {
    return char_vec_insert(&str->data, index, c);
}

static char *string_to_cstr(string *str) {
    char *cstr = (char *)malloc((str->data.len + 1 * sizeof(char)));

    for (i32 i = 0; i < str->data.len; i++) {
        cstr[i] = str->data.arr[i];
    }

    return cstr;
}

static u64 string_hash(string *str) {
    u64 hash = 5381;
    int c;

    while ((c = *str->data.arr++))
        hash = ((hash << 5) + hash) + c;

    return hash;
}

static void string_free(string *str) { char_vec_free(&str->data); }
