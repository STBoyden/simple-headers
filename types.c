#include "types.h"
#include "sstring.h"

size_t Type_sizeof(Type type) {
  switch (type) {
    case TYPE_BOOL:
      return sizeof(bool);
    case TYPE_U8:
    case TYPE_I8:
      return sizeof(u8);
    case TYPE_U16:
    case TYPE_I16:
      return sizeof(u16);
    case TYPE_U32:
    case TYPE_I32:
    case TYPE_F32:
      return sizeof(u32);
    case TYPE_U64:
    case TYPE_I64:
    case TYPE_F64:
      return sizeof(u64);
    case TYPE_U128:
    case TYPE_I128:
      return sizeof(u128);
    case TYPE_STR:
      return STRING_SIZE_MAX * sizeof(char);
    default:
      return 0;
  }
}

size_t Type_hash(Type type, void *ptr) {
  switch (type) {
    case TYPE_STRING: {
      String *s = (String *)ptr;
      return Type_hash(TYPE_STR, s->data.arr);
    };
    case TYPE_STR: {
      u64 hash = 5381;
      u8 c;

      if (ptr ==0x0) {
        return 0;
      }

      str s = (str)ptr;
      size_t size = strlen(s) * sizeof(char);
      str inner = (str) malloc(size);
      memccpy(inner, s, 0, size);

      while ((c = *s++))
          hash = ((hash << 5) + hash) + c;

      free(inner);
      return hash;
    };
    case TYPE_BOOL:
      return (size_t) * ((bool *)(ptr));
    case TYPE_U8:
      return (size_t) * ((u8 *)(ptr));
    case TYPE_U16:
      return (size_t) * ((u16 *)(ptr));
    case TYPE_U32:
      return (size_t) * ((u32 *)(ptr));
    case TYPE_U64:
      return (size_t) * ((u64 *)(ptr));
    case TYPE_U128:
      return (size_t) * ((u128 *)(ptr));
    case TYPE_I8:
      return (size_t) * ((i8 *)(ptr));
    case TYPE_I16:
      return (size_t) * ((i16 *)(ptr));
    case TYPE_I32:
      return (size_t) * ((i32 *)(ptr));
    case TYPE_I64:
      return (size_t) * ((i64 *)(ptr));
    case TYPE_I128:
      return (size_t) * ((i128 *)(ptr));
    case TYPE_F32:
      return (size_t) * ((f32 *)(ptr));
    case TYPE_F64:
      return (size_t) * ((f64 *)(ptr));
    default:
      break;
  }
}
