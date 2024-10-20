#ifndef CPU_ERROR_H
#define CPU_ERROR_H

void do_error(cpu_t *cpu);
int set_error(int err);


extern int error_code;

enum error_codes {
	err_none,
	err_phys_mem_not_present,
	err_bad_opcode
};

#endif