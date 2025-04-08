#include "cpu.h"
#include "opcodes.h"
#include "memory.h"


typedef  void (*opcode_handler_t)(cpu_t *);

opcode_handler_t *opcodes_funcs = NULL;

void exit_opcode() {
	free(opcodes_funcs);
}

void init_opcodes() {
	atexit(exit_opcode);
	opcodes_funcs = calloc(256, sizeof(opcode_handler_t));
}


void do_opcode(cpu_t *cpu) {
	if (cpu->r.r_pc >= cpu->mem_size) {
		cpu->r.interrupt = CPU_INT_OUT_BOUND;
		return;
	}

	u8 opcode = cpu->memory[cpu->r.r_pc];

	if (opcodes_funcs[opcode] != NULL)
		opcodes_funcs[opcode](cpu);
	else
		cpu->r.interrupt = CPU_INT_BADOPCODE;
}
