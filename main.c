#include <stdio.h>
#include "cpu.h"
#include "opcodes.h"

int main() {
	cpu_t *cpu = new_cpu();
	cpu->memory[0] = OPC_push_u8_as_u8;
	cpu->memory[1] = 0x42;

	do_opcode(cpu);

	dump_registers(cpu);
	free_cpu(cpu);
	return 0;
}