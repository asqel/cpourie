#include <stdio.h>
#include "cpu.h"
#include "opcodes.h"
#include "cpu_error.h"

int main() {
	init_opcodes();
	cpu_t *cpu = new_cpu(0x10000);
	cpu->memory[0] = 0b00000001;
	cpu->memory[1] = 0b10101100;
	cpu->memory[2] = 0x88;
	cpu->memory[3] = 0x88;
	cpu->memory[4] = 0x88;
	cpu->memory[5] = 0x88;
	dump_registers(cpu);
	while (1) {
		if (!cpu->is_halted)
			do_opcode(cpu);
		if (error_code != err_none)
			do_error(cpu);
	}
	dump_registers(cpu);
	free_cpu(cpu);
	return 0;
}
