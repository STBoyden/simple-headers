#pragma once

#include <stdlib.h>
#include <string.h>

// aliases for primitives

// str - stack allocated string
typedef char* str;

#define STRING_SIZE_MAX 100

// integers
#ifndef __cplusplus
    typedef unsigned char bool;
    enum bool { false = 0, true = 1 };
    #ifndef _SIZE_T
        typedef unsigned long long size_t;
        #define _SIZE_T size_t
    #endif
#else
    #error These headers are intended for C projects only.
#endif

typedef unsigned char       u8;
typedef unsigned short int  u16;
typedef unsigned int        u32;
typedef unsigned long       u64;
typedef unsigned long long  u128;

typedef char        i8;
typedef short int   i16;
typedef int         i32;
typedef long        i64;
typedef long long   i128;

// floating points
typedef float   f32;
typedef double  f64;

typedef enum {
    TYPE_NULL,
    TYPE_BOOL,
    TYPE_STR,
    TYPE_STRING,
    TYPE_U8,
    TYPE_U16,
    TYPE_U32,
    TYPE_U64,
    TYPE_U128,
    TYPE_I8,
    TYPE_I16,
    TYPE_I32,
    TYPE_I64,
    TYPE_I128,
    TYPE_F32,
    TYPE_F64,
} Type;

extern size_t Type_sizeof   (Type);
extern size_t Type_hash     (Type, void*);
