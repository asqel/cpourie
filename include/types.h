#ifndef TYPES_H
#define TYPES_H

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

typedef int8_t  i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;

typedef uint8_t  u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

#define MAX_u32 ((u32)0xFFFFFFFF)
#define MAX_u16 ((u16)0x0000FFFF)
#define MAX_u8  ((u16)0x000000FF)

#define MAX_i32 ((u32)0x7FFFFFFF)
#define MAX_i16 ((u16)0x00007FFF)
#define MAX_i8  ((u16)0x0000007F)

#define MIN_i32 ((u32)0xFFFFFFFF)
#define MIN_i16 ((u16)0x0000FFFF)
#define MIN_i8  ((u16)0x000000FF)

#endif