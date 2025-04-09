| OPCODE | mnemonic |   name   | description | doc |
|--------|----------|----------|-------------|-----|
|  0x01  |    ld    |   load   | load a constant to regiter |  [ld](instructions/load.md)   |
|        |          |          |             |     |



////
Integers instructions

ld A,  CONST:T
	0x01 0000TT11 ...(CONST:T)
ld A, [CONST]:T
	0x01 0001TT11 ...(CONST:u32)
ld A, [PC + B + CONST]:T
	0x01 TTBBBB01 ...(CONST:u8)
ld A, [PC + CONST:Y]:T
	0x01 YYTT0000 ...(CONST:Y)
ld A, [[PC + CONST:Y]]:T
	0x01 YYTT1000 ...(CONST:Y)
ld A, [[PC + B]]:T
	0x02 TTBBBB00
ld A, [B + CONST]:T
	0x02 BBBBTT11 ...(CONST:u16)
	0x02 BBBBTT01 ...(CONST:u8)
	0x02 BBBBTT10 ...(CONST:u32)

st [CONST]:T, A
	0x03 AAAATT00 ...(CONST:u32)
st [PC + CONST]:T, A
	0x03 AAAATT01 ...(CONST:u32)
st [[PC + CONST]]:T, A
	0x03 AAAATT10 ...(CONST:u32)
st [B + CONST]:T, A
	0x04 11AAAATT BBBB0000 ...(CONST:u32)
st [B + CONST1:Y]:T, CONST2
	0x04 10BBBBTT YY000000 ...(CONST2:T) ...(CONST1:Y)
st [PC + B + CONST:Y]:T, A
	0x04 10BBBBTT YYAAAA11 ...(CONST:Y)
st [PC + B + CONST1:Y]:T, CONST2
	0x04 10BBBBTT YY000010 ...(CONST2:T) ...(CONST1:Y)
st [[PC + B]]:T, CONST
	0x04 01BBBBTT ...(CONST:T)
st [[PC + B]]:T, A
	0x04 00BBBBTT AAAA0000

mov A, B
	0x05 AAAABBBB
mov A, PC
	0x06 AAAA0001
mov A, STATUS
	0x06 AAAA0010
mov STATUS, A
	0x06 AAAA0011

add A, B
	0xA0 AAAABBBB
add A, CONST:T // T == u32 or u16
	0xA1 AAAATT00 ...(CONST:T)
add A, [B]:u32
	0xA2 AAAABBBB
add A, [B]:u16
	0xA3 AAAABBBB
add A, [B]:u8
	0xA4 AAAABBBB
add A, [[B]]:u32
	0xA5 AAAABBBB
add A, [[B]]:u16
	0xA6 AAAABBBB
add A, [[B]]:u8
	0xA7 AAAABBBB

sub A, B
sub A, CONST:T // T == u32 or u16
sub A, [B]:T // T == u32 or u16
sub A, [[B]]:T // T == u32 or u16

Imul A, B
Imul A, CONST:T // T == i32 or i16

Umul A, B
Umul A, CONST:T // T == u32 or u16


Idiv A, B
Udiv A, B

Imod A, B
Umod A, B

// bitwise
Band A, B
Band A, CONST:u32
Bor A, B
Bor A, CONST:u32
Bnot A
Bxor A, B
Bxor A, CONST:u32

//logical
Land A, B
Land A, CONST:u32
Lor A, B
Lor A, CONST:u32
Lnot A
Lxor A, B
Lxor A, CONST:u32

Ilshift A, B
Ilshift A, CONST:u32
Ulshift A, B
Ulshift A, CONST:u32

cmp A, B
cmp A, CONST:u32
cmp A, [B]
cmp [B], [B]


// A:regeister/constant
// MOD: Uless, Ugreater, equal, Iless, Igreater,
//		Uless_eq, Ugreater_eq, Iless_eq, Igreater_eqy
//		always true
jmp_MOD A
jmp_MOD [A]
jmp_MOD PC + A
jmp_MOD PC + [A]
Jmp_MOD A + [A]
jmp_MOD PC + [PC + A]

call_MOD A
call_MOD [A]
call_MOD PC + A
call_MOD PC + [A]
call_MOD A + [A]
call_MOD PC + [PC + A]


halt


// integer and float

movh A, B	// move higher half of float in B into A
movl A, B	// move lower half of float in B into A
