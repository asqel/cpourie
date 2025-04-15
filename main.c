#include <stdio.h>
#include <string.h>
#include "cpu.h"
#include "opcodes.h"

int main(int argc, char **argv) {
	init_opcodes();
	cpu_t *cpu = new_cpu(0x10000);
	cpu->memory[0] = 0x6c;
	cpu->memory[1] = 0b11111011;
	cpu->memory[2] = 0x01;
	cpu->memory[3] = 0x23;
	cpu->memory[4] = 0x45;
	cpu->memory[5] = 0x99;

	while (1) {
		if (cpu->r.interrupt != 0)
		{
			printf("CPU RECEIVED INTERRUPT %d\n", cpu->r.interrupt);
			break;
		}
		if (!cpu->is_halted)
			do_opcode(cpu);
	}

	//FILE *f = fopen("./memory.dat", "w+");
	//fwrite(cpu->memory, 1, cpu->mem_size, f);
	//fclose(f);

	if (argc == 2 && (strcmp(argv[1], "--dump") == 0 || strcmp(argv[1], "-d") == 0))
		dump_registers(cpu);
	free_cpu(cpu);
	return 0;
}
