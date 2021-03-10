#pragma once

#include <stdlib.h>

// aliases for primitives

// str - stack allocated string
typedef char *str;

// integers
#ifndef __cplusplus
typedef unsigned char bool;
enum bool { false = 0, true = 1 };
#else
#error These headers are intended for C projects only.
#endif
typedef unsigned char u8;
typedef unsigned short int u16;
typedef unsigned int u32;
typedef unsigned long u64;
typedef unsigned long long u128;

typedef char i8;
typedef short int i16;
typedef int i32;
typedef long i64;
typedef long long i128;

// floating points
typedef float f32;
typedef double f64;

// work around for not being able to call T_free when freeing a dictionary or
// vec. is it hacky? yes. is there a better way? yes, probably. do i know what
// the better way is? absolutely not. the joys of generic programming in C i
// guess.
static void str_free(str *s) {}
static void bool_free(bool *b) {}
static void u8_free(u8 *u) {}
static void u16_free(u16 *u) {}
static void u32_free(u32 *u) {}
static void u64_free(u64 *u) {}
static void u128_free(u128 *u) {}
static void i8_free(i8 *i) {}
static void i16_free(i16 *i) {}
static void i32_free(i32 *i) {}
static void i64_free(i64 *i) {}
static void i128_free(i128 *i) {}
static void f32_free(f32 *f) {}
static void f64_free(f64 *f) {}

static size_t str_hash(str s) {

    u64 hash = 5381;
    int c;

    while ((c = *s++))
        hash = ((hash << 5) + hash) + c;

    return hash;
}
static bool bool_hash(bool *b) { return *b; }
static u8 u8_hash(u8 *u) { return *u; }
static u16 u16_hash(u16 *u) { return *u; }
static u32 u32_hash(u32 *u) { return *u; }
static u64 u64_hash(u64 *u) { return *u; }
static u128 u128_hash(u128 *u) { return *u; }
static i8 i8_hash(i8 *i) { return *i; }
static i16 i16_hash(i16 *i) { return *i; }
static i32 i32_hash(i32 *i) { return *i; }
static i64 i64_hash(i64 *i) { return *i; }
static i128 i128_hash(i128 *i) { return *i; }
static f32 f32_hash(f32 *f) { return *f; }
static f64 f64_hash(f64 *f) { return *f; }
