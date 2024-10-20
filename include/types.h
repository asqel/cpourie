#ifndef TYPES_H
#define TYPES_H


#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

#undef i8
#undef i16
#undef i32
#undef i64
#undef u8
#undef u16
#undef u32
#undef u64
#undef u0

#undef I8
#undef I16
#undef I32
#undef I64
#undef U8
#undef U16
#undef U32
#undef U64
#undef U0

#define i8 		int8_t
#define i16 	int16_t
#define i32 	int32_t
#define i64 	int64_t

#define u8 		uint8_t
#define u16 	uint16_t
#define u32 	uint32_t
#define u64 	uint64_t
#define u0 		void

#define I8 		int8_t
#define I16 	int16_t
#define I32 	int32_t
#define I64 	int64_t

#define U8 		uint8_t
#define U16 	uint16_t
#define U32 	uint32_t
#define U64 	uint64_t
#define U0 		void

#define u48 u64
#define i48 i64

#define MAX_u48 ((u48)0xFFFFFFFFFFFF)
#define MAX_u32 ((u32)0x0000FFFFFFFF)
#define MAX_u16 ((u16)0x00000000FFFF)
#define MAX_u8  ((u16)0x0000000000FF)

#define SIZEOF_u48 6
#define SIZEOF_u32 4
#define SIZEOF_u16 2
#define SIZEOF_u8  1
#define SIZEOF_double 8

#endif