#include "cpu.h"
#include "cpu_error.h"

int error_code = 0;
int err_count = 0;

int set_error(int err) {
	if (err == err_none)
		return 0;
	error_code = err;
	err_count++;
	return 1;
}

void do_error(cpu_t *cpu) {
	printf("ERROR ON CPU %d\n", error_code);
	dump_registers(cpu);
	free_cpu(cpu);
	exit(1);
	// implement interrupt
}