#pragma once

#include <stdio.h>

// a wrapper over a char_vec to implement a simple heap allocated string type

#include "types.h"

#define T char

#include "vec.h"

typedef struct {
    char_vec data;
    size_t *len;
} string;

// string_new - Creates a new string from a str (aka const char*).
static string string_new(str s) {
    string str;
    str.data = char_vec_new();
    str.len = &str.data.len;

    for (i32 i = 0; i < strlen(s); i++) {
        char_vec_push(&str.data, s[i]);
    }

    return str;
}

// string_push - Appends the given char to the end of the given string.
static char string_push(string *string_ref, char c) {
    return char_vec_push(&string_ref->data, c);
}

// string_pop - Pops the last character to the end of the given string.
static char string_pop(string *string_ref) { return char_vec_pop(&string_ref->data); }

// string_insert - Inserts the given c, at the given index into the given string.
static char string_insert(string *string_ref, char c, size_t index) {
    return char_vec_insert(&string_ref->data, index, c);
}

// string_to_cstr - returns a str that can be printed easily.
static str string_to_cstr(string *string_ref) {
    str cstr = (str) malloc((string_ref->data.len + 1 * sizeof(char)));

    for (i32 i = 0; i < string_ref->data.len; i++) {
        cstr[i] = string_ref->data.arr[i];
    }

    return cstr;
}

// string_hash - returns the hash of the string
static u64 string_hash(string *string_ref) {
    u64 hash = 5381;
    if (string_ref->data.arr == NULL)
        return hash;

    u8 c;
    str inner = malloc(string_ref->data.len * sizeof(char));
    strcpy(inner, string_ref->data.arr);
    string data_str = string_new(inner);

    while ((c = *data_str.data.arr++))
        hash = ((hash << 5) + hash) + c;

    return hash;
}

// string_free - frees the contents of the string
static void string_free(string *string_ref) {
    char_vec_free(&string_ref->data);
}

// string_length - gets the length of the string
static size_t string_length(string *string_ref) { return *string_ref->len; }
