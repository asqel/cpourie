| OPCODE | mnemonic |   name   | description | doc |
|--------|----------|----------|-------------|-----|
|  0x01  |    ld    |   load   | load a constant to regiter |  [ld](instructions/load.md)   |
|        |          |          |             |     |



Used opcode

| low\\high| 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | A | B | C | D | E | F |
|----------|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|
|    0     |   |   | X | X |   |   | X |   | X | X | X | X | X | X |   | X |
|    1     |   |   | X | X |   |   |   |   | X | X | X | X | X |   |   | X |
|    2     |   |   | X | X |   |   |   |   | X | X | X | X | X |   | X | X |
|    3     |   |   | X | X |   | X |   | X | X | X | X | X | X |   |   | X |
|    4     |   |   | X | X |   |   |   |   | X | X | X | X | X |   |   | X |
|    5     |   |   | X | X |   |   |   |   | X | X |   | X | X |   |   | X |
|    6     |   |   | X | X |   |   |   |   | X | X |   | X | X |   |   | X |
|    7     |   |   |   | X |   |   |   |   | X | X |   | X | X |   |   | X |
|    8     |   |   |   |   |   |   |   |   | X | X | X |   | X |   | X | X |
|    9     |   |   |   |   |   |   |   |   |   |   | X |   | X |   |   | X |
|    A     |   |   |   |   |   |   |   |   |   |   | X |   |   |   |   | X |
|    B     |   |   |   |   |   |   | X |   |   |   | X |   |   |   |   | X |
|    C     |   |   |   |   | X |   | X |   |   |   |   |   |   |   |   | X |
|    D     |   |   |   |   | X |   | X |   |   |   |   |   |   |   |   | X |
|    E     |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |
|    F     |   |   |   |   |   |   |   |   | X |   |   |   |   |   |   |   |

type T
	00 : u8
	01 : u16
	10 : u32
	11 : INVALIDE

////
Integers instructions


ld A,  CONST:T
	0x6C AAAATT11 ...(CONST:T)
ld A, [CONST]:T
	0x6C AAAATT10 ...(CONST:u32)
ld A, [PC + CONST:Y]:T
	0x6A YYTTAAAA ...(CONST:Y)
ld A, [[PC + CONST:Y]]:T
	0x60 YYTTAAAA ...(CONST:Y)
ld A, [PC + B + CONST:Y]:T
	0x6B BBBBAAAA TTYY0000 ...(CONST:T)
ld A, [[PC + B]]:T
	0x6B BBBBAAAA TT000001
ld A, [B]:T
	0x4C BBBBTT00 AAAA0000


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

sub A, B
	0xA8 AAAABBBB
sub A, CONST:T
	0xA9 AAAATT00 ...(CONST:T)
sub A, [B]:u32
	0xAA AAAABBBB
sub A, [B]:u16
	0xAB AAAABBBB
sub A, [B]:u8
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

Urshift A, B
	0x36 AAAABBBB
Urshift A, CONST:u8
	0x37 AAAA0000 CONST

cmp A, B
	0xC0 AAAABBBB
cmp A, CONST:T
	0xC1 AAAATT00 ...(CONST:T)
cmp [A], CONST:T
	0xC1 AAAATT11 ...(CONST:T)
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
cmod A:u32, CONST:T
	0xC9 AAAATT00 ...(CONST:T)


// A:regeister/constant
// MOD: Uless, Ugreater, equal, Iless, Igreater,
//		Uless_eq, Ugreater_eq, Iless_eq, Igreater_eq
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
jmp_M PC + [PC + A]:u32
	0x85 MMMMAAAAA
jmp_M PC + [PC + CONST:T]:u32
	0x86 MMMMTT00 ...(CONST:T)
jmp_M PC + CONST:T
	0x87 MMMMTT00  ...(CONST:T)
jmp_M [PC + A]:u32
	0x88 MMMMAAAA
jmp_M [PC + CONST:T]
	0x89 MMMMTT00  ...(CONST:T)

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
call_M [PC + A]
	0x98 MMMMAAAA
call_M [PC + CONST:T]
	0x99 MMMMTT00  ...(CONST:T)

push A:T
	0xE2 AAAATT00
push CONST:T
	0xE2 0000TT11 ...(CONST:T)
push [A]:T
	0xE2 AAAATT10

pop A:T
	0xE8 AAAATT00
pop [A]:T
	0xE8 AAAATT11

swap A, B
	0xD0 AAAABBBB

ret
	8F

set_sdt A, B
	0xF0 AAAABBBB
	// set sdt entry contained in A to the address contained in B (only kernel mod)

set_ddt A, B
	0xF1 AAAABBBB
	// set ddt entry contained in A to the address contained in B (only kernel mod or driver mod)

syscall X
	0xF2 XXXXXXXX
	call the sdt entry 0bXXXXXXXX and switch to kernel mode

drivcall X
	0xF3 XXXXXXXX
	call the sdt entry 0bXXXXXXXX and switch to driver mode

sret
	0xF4
	return from syscall (only in kernel mod)

dret
	0xF5
	return from drivcall (only in driver mod)

set_umem
	0xF6
	set umem from register si (only in kernel mod)

set_dmem
	0xF7
	set dmem from register si (only in kernel mod)

set_lvl_sp:
	0xF8
	set lvl_sp from register si (only kernel mod)

set_lvl_bp:
	0xF9
	set lvl_bp from register si (only kernel mod)

set_lvl_len:
	0xFA
	set lvl_len from register si (only kernel mod)

read_lvl_sp:
	0xFB
	read to si the level stack pointer (only in kernel mod)

read_lvl_bp:
	0xFC

read_lvl_stack_len:
	0xFD