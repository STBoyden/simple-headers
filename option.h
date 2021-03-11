#include "sstring.h"
#include <stdio.h>

#ifndef T
#error option.h: T not defined.
#endif

#define GNG_(type, name) type##name
#define GNG(type, name) GNG_(type, name)

#define STR_(x) #x
#define STR(x) STR_(x)

typedef enum { None, Some } GNG(T, _option_enum);

typedef union {
    GNG(T, _option_enum) opt_enum;
    T data;
} GNG(T, _option);

/* typedef struct { */
/*     T data; */
/*     GNG(T, _option_enum) _option; */
/* } GNG(T, _option); */

/* static void GNG(T, _option_init)(GNG(T, _option) * opt) { */
/*     opt->opt_enum = None; */
/* } */

static GNG(T, _option) GNG(T, _option_new)(T data) {
    GNG(T, _option) opt;

    if (!data) {
        GNG(T, _option_init)(&opt);
        opt.opt_enum = None;
    } else {
        opt.data = data;
    }

    return opt;
}

static T GNG(T, _option_unwrap)(GNG(T, _option) *opt) {
    if (opt->data != NULL)
        return opt->data;
    else {
        fprintf(stderr, "Could not unwrap " STR(GNG(T, _option)) "\n");
    }
}

static T GNG(T, _option_expect)(GNG(T, _option) *opt, const str message) {}
