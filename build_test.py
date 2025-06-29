"""
// store at 0x1000 as u32 *
// do contain number of phib to compute
// re :x
// mi :y
// fa :z
// so :ptr
fib:
	push so, re, mi, fa
	mov so, 0x1000; 0x6c 01110111, 0x1000
	mov re, 0; 0x6c 00110011, 0
	mov mi, 1; 0x6c 01000011, 1
	mov fa, 1; 0x6c 01010011, 1
	.loop; address = 4 + 3 + 3 + 3 = 13
		cmp do, 0; 0xc1 00000000, 0
		jleq .end; 0x81 10000000, 500:u32

		mov re, mi; 0x6d 00100100
		mov mi, fa; 0x6d 01000101
		add fa, re; 0x6d 01010010
		st [so]:u32, fa; 0x53 1110110 01110000, 0 0 0 0
		add so, 4; 0xa1 01110000, 4
		sub do, 1; 0xa9 00000000, 1

		jmp .loop; 0x81 10010000, 13:u32
	.end:
	pop fa, mi, re, so
	ret
"""

bytes = [
    #fib:
	0x6c, 0b00000011, 10, #mov do, 10
	0x6c, 0b01110111, 0x00, 0x20, #mov so, 0x1000
	0x6c, 0b00100011, 0,#mov re, 0
	0x6c, 0b01000011, 1,#mov mi, 1
	0x6c, 0b01010011, 1,#mov fa, 1
	0x6c, 0b00000011, 10,#mov do, 10
	#addr = 19 #.loop
	0xc1, 0b00000000, 0,#	cmp do, 0
	0x87, 0b01111000, 0x35, 0x0 ,0, 0,#	jleq .end

	0x6d, 0b00100100,#	mov re, mi
	0x6d, 0b01000101,#	mov mi, fa
	0xa0, 0b01010010,#	add fa, re
	0x53, 0b11010110, 0b01110000, 0, 0, 0, 0,#	st [so]:u32, fa
	0xa1, 0b01110000, 4,#	add so, 4
	0xa9, 0b00000000, 1,#	sub do, 1

	0x87, 0b10011000, 0xe4, 0xff, 0xff, 0xff, # -28 # jmp .loop
	0,# halt
]

f = open("./test.bin", "wb")
f.write(bytearray(bytes))
f.close()