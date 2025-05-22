// store at 0x1000 as u32 *
// do contain number of phib to compute
// re :x
// mi :y
// fa :z
// so :ptr
fib:
	push so, re, mi, fa
	mov so, 0x1000
	mov re, 0
	mov mi, 1
	mov fa, 1
	.loop
		cmp do, 0
		jleq .end

		mov re, mi
		mov mi, fa
		add fa, re
		st [so]:u32, fa
		add so, 4
		sub do, 1

		jmp .loop
	.end:
	pop fa, mi, re, so
	ret

