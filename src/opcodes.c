#include "cpu.h"
#include "opcodes.h"
#include "cpu_error.h"
#include "memory.h"


typedef  int (*opcode_handler_t)(cpu_t *);

opcode_handler_t opcodes_funcs[256][4] = {{NULL}};

void init_opcodes() {
	opcodes_funcs[1][0] = do_ld_01_A;
}


int do_opcode(cpu_t *cpu) {
	opcodes_funcs[0][0] = do_opcode_mov;
	if (cpu->r.r_pc >= cpu->mem_size)
		return set_error(err_phys_mem_not_present);

	u8 opcode = cpu->memory[cpu->r.r_pc];

	for (int i = 0; opcodes_funcs[opcode][i] != NULL; i++) {
		int ret = (opcodes_funcs[opcode][i])(cpu);
		// 1 for error, -1 for continue, 0 for ok
		if (ret == 1)
			return 1;
		if (ret == 0)
			return set_error(err_none);
		if (ret == -1)
			continue;
		else {
			fprintf(stderr, "Invalide opcode function return value in do_opcode (0x%c%c | %d)\n", "0123456789ABCDEF"[opcode >> 4], "0123456789ABCDEF"[opcode & 0xf], ret);
		}
	}
	return set_error(err_bad_opcode);
}
