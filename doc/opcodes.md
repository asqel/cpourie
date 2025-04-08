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
st [PC + CONST]:T, A
st [[PC + CONST]]:T, A
st [B + CONST]:T, A
st [B + CONST1]:T, CONST2
st [PC + B + CONST]:T, A
st [PC + B + CONST1]:T, CONST2
st [[PC + B]], CONST
st [[PC + B]], A

mov A, B
mov A, PC
mov A, STATUS
mov STATUS, A

add A, B

add A, CONST:T // T == u32 or u16
add A, [B]:T // T == u32 or u16
add A, [[B]]:T // T == u32 or u16

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
