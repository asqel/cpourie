#include "cpu.h"
#include "cpu_error.h"

int error_code = 0;

int set_error(int err) {
	error_code = err;
	return 1;
}

void do_error(cpu_t *cpu) {
	printf("ERROR ON CPU\n");
	dump_registers(cpu);
	free_cpu(cpu);
	exit(1);
	// implement interrupt
}