#pragma once

#include "sstring.h"
#include "types.h"

// just implementing generic vectors for each of the primative types

#define T u8
#include "vec.h"

#define T u16
#include "vec.h"

#define T u32
#include "vec.h"

#define T u64
#include "vec.h"

#define T u128
#include "vec.h"

#define T i8
#include "vec.h"

#define T i16
#include "vec.h"

#define T i32
#include "vec.h"

#define T i64
#include "vec.h"

#define T i128
#include "vec.h"

#define T f32
#include "vec.h"

#define T f64
#include "vec.h"

#define T string
#include "vec.h"
