| OPCODE | mnemonic |   name   | description | doc |
|--------|----------|----------|-------------|-----|
|  0x01  |    ld    |   load   | load a constant to regiter |  [ld](instructions/load.md)   |
|        |          |          |             |     |



Used opcode

| low\\high| 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | A | B | C | D | E | F |
|----------|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|
|    0     |   |   | X | X |   |   |   |   | X | X | X | X | X |   |   |   |
|    1     |   |   | X | X |   |   |   |   | X | X | X | X | X |   |   |   |
|    2     |   |   | X | X |   |   |   |   | X | X | X | X | X |   |   |   |
|    3     |   |   | X | X |   | X |   | X | X | X | X | X | X |   |   |   |
|    4     |   |   | X | X |   |   |   |   | X | X | X | X | X |   |   |   |
|    5     |   |   | X | X |   |   |   |   | X | X | X | X | X |   |   |   |
|    6     |   |   | X |   |   |   |   |   | X | X | X | X | X |   |   |   |
|    7     |   |   |   |   |   |   |   |   | X | X | X | X | X |   |   |   |
|    8     |   |   |   |   |   |   |   |   |   |   | X |   | X |   |   |   |
|    9     |   |   |   |   |   |   |   |   |   |   | X |   | X |   |   |   |
|    A     |   |   |   |   |   |   |   |   |   |   | X |   |   |   |   |   |
|    B     |   |   |   |   |   |   |   |   |   |   | X |   |   |   |   |   |
|    C     |   |   |   |   | X |   | X |   |   |   | X |   |   |   |   |   |
|    D     |   |   |   |   | X |   | X |   |   |   |   |   |   |   |   |   |
|    E     |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |
|    F     |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |

////
Integers instructions

ld A,  CONST:T
	0x6C 0000TT11 ...(CONST:T)
ld A, [CONST]:T
	0x6C 0001TT11 ...(CONST:u32)
ld A, [PC + B + CONST]:T
	0x6C TTBBBB01 ...(CONST:u8)
ld A, [PC + CONST:Y]:T
	0x6C YYTT0000 ...(CONST:Y)
ld A, [[PC + CONST:Y]]:T
	0x6C YYTT1000 ...(CONST:Y)
ld A, [[PC + B]]:T
	0x4C TTBBBB00
ld A, [B + CONST]:T
	0x4C BBBBTT11 ...(CONST:u16)
	0x4C BBBBTT01 ...(CONST:u8)
	0x4C BBBBTT10 ...(CONST:u32)


st [CONST]:T, A
	0x73 AAAATT00 ...(CONST:u32)
st [PC + CONST]:T, A
	0x73 AAAATT01 ...(CONST:u32)
st [[PC + CONST]]:T, A
	0x73 AAAATT10 ...(CONST:u32)
st [B + CONST]:T, A
	0x53 11AAAATT BBBB0000 ...(CONST:u32)
st [B + CONST1:Y]:T, CONST2
	0x53 10BBBBTT YY000000 ...(CONST2:T) ...(CONST1:Y)
st [PC + B + CONST:Y]:T, A
	0x53 10BBBBTT YYAAAA11 ...(CONST:Y)
st [PC + B + CONST1:Y]:T, CONST2
	0x53 10BBBBTT YY000010 ...(CONST2:T) ...(CONST1:Y)
st [[PC + B]]:T, CONST
	0x53 01BBBBTT ...(CONST:T)
st [[PC + B]]:T, A
	0x53 00BBBBTT AAAA0000


mov A, B
	0x6D AAAABBBB
mov A, PC
	0x4D AAAA0001
mov A, STATUS
	0x4D AAAA0010
mov STATUS, A
	0x4D AAAA0011


add A, B
	0xA0 AAAABBBB
add A, CONST:T
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
	0xA8 AAAABBBB
sub A, CONST:T
	0xA9 AAAATT00 ...(CONST:T)
sub A, [B]:u16
	0xA9 AAAABBBB
sub A, [B]:u32
	0xAA AAAABBBB
sub A, [[B]]:u16
	0xAB AAAABBBB
sub A, [[B]]:u32
	0xAC AAAABBBB


Imul A, B
	0xB0 AAAABBBB
Imul A, CONST:T
	0xB1 AAAATT00 ...(CONST:T)
Umul A, B
	0xB2 AAAABBBB
Umul A, CONST:T
	0xB3 AAAATT00 ...(CONST:T)


Idiv A, B
	0xB4 AAAABBBB
Udiv A, B
	0xB5 AAAABBBB

Imod A, B
	0xB6 AAAABBBB
Umod A, B
	0xB7 AAAABBBB


// bitwise
Band A, B
	0x20 AAAABBBB
Band A, CONST:T
	0x21 AAAATT00 ...(CONST:T)
Bor A, B
	0x22 AAAABBBB
Bor A, CONST:T
	0x23 AAAATT00 ...(CONST:T)
Bnot A
	0x24 AAAA0000
Bxor A, B
	0x25 AAAABBBB
Bxor A, CONST:T
	0x26 AAAATT00 ...(CONST:T)

// Logical
Land A, B
	0x30 AAAABBBB
Lor A, B
	0x31 AAAABBBB
Lnot A
	0x32 AAAA0000
Lxor A, B
	0x33 AAAABBBB


Ulshift A, B
	0x34 AAAABBBB
Ulshift A, CONST:u8
	0x35 AAAA0000 CONST

cmp A, B
	0xC0 AAAABBBB
cmp A, CONST:uT
	0xC1 AAAATT00 ...(CONST:T)
cmp A:u8, [B]:u8
	0xC2 AAAABBBB
cmp A:u16, [B]:u16
	0xC3 AAAABBBB
cmp A:u32, [B]:u32
	0xC4 AAAABBBB
cmp [A]:u8, [B]:u8
	0xC5 AAAABBBB
cmp [A]:u16, [B]:u16
	0xC6 AAAABBBB
cmp [A]:u32, [B]:u32
	0xC7 AAAABBBB

// check modulo set flag of modulo if A % B != 0
cmod A, B
	0xC8 AAAABBBB
cmod A, CONST:T
	0xC9 AAAATT00 ...(CONST:T)


// A:regeister/constant
// MOD: Uless, Ugreater, equal, Iless, Igreater,
//		Uless_eq, Ugreater_eq, Iless_eq, Igreater_eqy
//		true, mod0 (modulo flag == 0), mod1

jmp_M A
	0x80 MMMMAAAA
jmp_M CONST
	0x81 MMMM0000 ...(CONST:u32)
jmp_M [A]
	0x82 MMMMAAAA
jmp_M PC + A
	0x83 MMMMAAAA
jmp_M PC + [A]
	0x84 MMMMAAAA
jmp_M PC + [PC + A]
	0x85 MMMMAAAAA
jmp_M PC + [PC + CONST:T]
	0x86 MMMMTT00 ...(CONST:T)
jmp_M PC + CONST:T
	0x87 MMMMTT00  ...(CONST:T)


call_M A
	0x90 MMMMAAAA
call_M CONST
	0x91 MMMM0000 ...(CONST:u32)
call_M [A]
	0x92 MMMMAAAA
call_M PC + A
	0x93 MMMMAAAA
call_M PC + [A]
	0x94 MMMMAAAA
call_M PC + [PC + A]
	0x95 MMMMAAAAA
call_M PC + [PC + CONST:T]
	0x96 MMMMTT00 ...(CONST:T)
call_M PC + CONST:T
	0x97 MMMMTT00  ...(CONST:T)
