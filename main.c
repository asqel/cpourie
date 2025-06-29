#include <stdio.h>
#include <string.h>
#include "cpu.h"
#include "opcodes.h"

typedef struct {
	char dump;
	char dump_mem;
	char step;
	char *prog;
	u32 mem_size;
} run_args_t;

int load_prog(cpu_t *cpu, char *prog) {
	FILE *f = fopen(prog, "rb");
	if (f == NULL) {
		perror(prog);
		return 1;
	}
	u32 len = 0;
	fseek(f, 0, SEEK_END);
	len = ftell(f);
	fseek(f, 0, SEEK_SET);
	if (len > cpu->mem_size - CPU_START_ADDR) {
		fprintf(stderr, "Program size (%d bytes) exceeds memory size (%d bytes).\n", len, cpu->mem_size);
		fclose(f);
		return 1;
	}
	fread(&cpu->memory[CPU_START_ADDR], 1, len, f);
	fclose(f);
	return 0;
}

run_args_t init_args(int argc, char **argv) {
	run_args_t args = {0};
	args.mem_size = CPU_START_ADDR + 0x2000;

	for (int i = 1; i < argc; i++) {
		if (strcmp(argv[i], "--dump") == 0 || strcmp(argv[i], "-d") == 0)
			args.dump = 1;
		else if (strcmp(argv[i], "--step") == 0 || strcmp(argv[i], "-s") == 0)
			args.step = 1;
		else if (strcmp(argv[i], "--mem-size") == 0 || strcmp(argv[i], "-m") == 0) {
			if (i + 1 < argc) {
				args.mem_size = strtoul(argv[++i], NULL, 0);
				if (args.mem_size == 0 || args.mem_size < CPU_START_ADDR + 0x1000) {
					fprintf(stderr, "Invalid memory size: %s\n", argv[i]);
					exit(1);
				}
			}
			else {
				fprintf(stderr, "Memory size option requires a value.\n");
				exit(1);
			}
		}
		else if (strcmp(argv[i], "--dump-mem") == 0 || strcmp(argv[i], "-dm") == 0)
			args.dump_mem = 1;
		else {
			if (args.prog != NULL) {
				fprintf(stderr, "Multiple program files specified: %s and %s\n", args.prog, argv[i]);
				exit(1);
			}
			args.prog = argv[i];
		}
	}
	if (args.prog == NULL) {
		fprintf(stderr, "No program file specified.\n");
		exit(1);
	}
	return args;
}

int main(int argc, char **argv) {
	run_args_t args = init_args(argc, argv);
	cpu_t *cpu = new_cpu(args.mem_size);
	init_opcodes();

	if (load_prog(cpu, args.prog) != 0) {
		free_cpu(cpu);
		return 1;
	}
	while (1) {
		if (cpu->r.interrupt != 0)
		{
			printf("CPU RECEIVED INTERRUPT %d at PC:0x%04X(%d)\n", cpu->r.interrupt, cpu->r.r_pc, cpu->r.r_pc);
			break;
		}
		if (!cpu->is_halted) {
			if (args.step) {
				if (getchar() == 'd')
					dump_registers(cpu);
			}
			do_opcode(cpu);
		}
		else
			break;
	}

	if (args.dump)
		dump_registers(cpu);
	if (args.dump_mem) {
		FILE *f = fopen("memory.bin", "wb");
		if (f == NULL) {
			perror("memory.bin");
			free_cpu(cpu);
			return 1;
		}
		fwrite(cpu->memory, 1, cpu->mem_size, f);
		fclose(f);
	}
	free_cpu(cpu);
	return 0;
}
