#include <stdio.h>
#include <string.h>
#include "cpu.h"
#include "opcodes.h"

int main(int argc, char **argv) {
	init_opcodes();
	cpu_t *cpu = new_cpu(0x10000);
	cpu->memory[0] = 0b00000001;
	cpu->memory[1] = 0b10101100;
	cpu->memory[2] = 0x88;
	cpu->memory[3] = 0x88;
	cpu->memory[4] = 0x88;
	cpu->memory[5] = 0x88;
	while (1) {
		if (cpu->r.interrupt != 0)
		{
			printf("CPU RECEIVED INTERRUPT %d\n", cpu->r.interrupt);
			break;
		}
		if (!cpu->is_halted)
			do_opcode(cpu);
	}
	if (argc == 2 && (strcmp(argv[1], "--dump") == 0 || strcmp(argv[1], "-d") == 0))
		dump_registers(cpu);
	free_cpu(cpu);
	return 0;
}
