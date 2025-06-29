mov do, 10
mov so, 0x1000
mov re, 0
mov mi, 1
mov fa, 1
mov do, 10
.loop
	cmp do, 0
	jleq 0x35; .end

	mov re, mi
	mov mi, fa
	add fa, re
	st [so]:u32, fa
	add so, 4
	sub do, 1

	jmp 19; .loop
	.end
	halt
