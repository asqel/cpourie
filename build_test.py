
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