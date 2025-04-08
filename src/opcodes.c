#include "cpu.h"
#include "opcodes.h"
#include "memory.h"


typedef  int (*opcode_handler_t)(cpu_t *);

opcode_handler_t opcodes_funcs[256] = {NULL};

void init_opcodes() {

}


void do_opcode(cpu_t *cpu) {
	if (cpu->r.r_pc >= cpu->mem_size) {
		cpu->r.interrupt = CPU_INT_PHYS_MEM;
		return;
	}

	u8 opcode = cpu->memory[cpu->r.r_pc];

	if (opcodes_funcs[opcode] != NULL)
		opcodes_funcs[opcode](cpu);

	cpu->r.interrupt = CPU_INT_BADOPCODE;
}
