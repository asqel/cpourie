#include <stdio.h>
#include "cpu.h"
#include "opcodes.h"
#include "cpu_error.h"

int main() {
	cpu_t *cpu = new_cpu(0x10000);
	cpu->memory[0] = 0b01111010;
	cpu->memory[1] = 0b00000111;
	cpu->memory[2] = 0xAB;
	cpu->memory[3] = 0xCD;
	while (1) {
		do_opcode(cpu);
		if (error_code != err_none)
			do_error(cpu);
	}
	dump_registers(cpu);
	free_cpu(cpu);
	return 0;
}