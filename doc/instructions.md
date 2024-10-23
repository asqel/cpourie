## types
every integer are store as little endian

### u8
8 bit / 1 Byte integer

### u16
16 bit / 2 Byte integer

### u32
32 bit / 4 Byte integer

### u48
48 bit / 6 Byte integer

### fpoint
fixed point number composed of two i32 (integer part, decimal part)

## registers

### integers
there are 7 integer registers (do, re, mi, fa, so, la, si)
each can hold 4 u48 values
we note them as R[N] (e.g. do[2]) with N starting at 0

### fpoints
they work the same as integer regsisters except that they can hold
6 fpoint values each and are called red, green, blue, magenta, yellow, cyan, white, black

## push V:X as Y

### description
push the value `V` of type `X` as type `Y`

### condition
`X <= Y`

### bits

`00000001 0000XXYY ... (V)`

XX / YY:
```
	u8 : 00
	u16: 01
	u32: 10
	u48: 11
```

### size
if X:
```
	u8 -> 3
	u16 -> 4
	u32 -> 6
	u48 -> 8
```

## push R[N] as Y

### description
push the value of the register `R` at `N` as `Y`

### bits

`00000001 1YYNNRRR`

R:
```
	do : 000
	re : 001
	mi : 010
	fa : 011
	so : 100
	la : 101
	si : 110
```
N:
```
	0 : 00
	1 : 01
	2 : 10
	3 : 11
```
YY:
```
	u8 : 00
	u16: 01
	u32: 10
	u48: 11
```

### size
2

## push R[N] (fpoint)

### description
push the fpoint value of the register `R` at `N`

### bits

`00000001 01NNNRRR`

R:
```

	red    : 000
	green  : 001
	blue   : 010
	magenta: 011
	yellow : 100
	cyan   : 101
	white  : 110
	black  : 111
```
N:
```
	0 : 000
	1 : 001
	2 : 010
	3 : 011
	4 : 100
	5 : 101
	6 : 110
	7 : 111
```

### size
2

## push V:fpoint

### description
push `V` an fpoint onto the stack

### bits

`00000010 ... (int_part:i32, dec_part:i32)`

### size
9

## pop R[N] as Y

### description
pop the value on top of the stack as `Y` and put it into register `R` at `N`

### bits
`00000011 0RRRNNYY`


R:
```
	do : 000
	re : 001
	mi : 010
	fa : 011
	so : 100
	la : 101
	si : 110
```
N:
```
	0 : 00
	1 : 01
	2 : 10
	3 : 11
```
YY:
```
	u8 : 00
	u16: 01
	u32: 10
	u48: 11
```

### size
2

## pop R[N] (fpoint)

### description
pop the value on top of the stack as an fpoint and put it into register `R` at `N`

### bits
`00000011 1RRRNNN0`

R:
```

	red    : 000
	green  : 001
	blue   : 010
	magenta: 011
	yellow : 100
	cyan   : 101
	white  : 110
	black  : 111
```
N:
```
	0 : 000
	1 : 001
	2 : 010
	3 : 011
	4 : 100
	5 : 101
	6 : 110
	7 : 111
```

### size
2