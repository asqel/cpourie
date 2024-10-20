#ifndef CPU_H
#define CPU_H

#include "types.h"

#define MEM_SIZE 0x10000

typedef struct {
	u48 r_do[7];
	u48 r_re[7];
	u48 r_mi[7];
	u48 r_fa[7];
	u48 r_so[7];
	u48 r_la[7];
	u48 r_si[7];

	u48 r_pc;
	u48 r_sp;
	u48 r_bp;
	u48 r_status;

	double r_red[6];
	double r_green[6];
	double r_blue[6];
	double r_magenta[6];
	double r_yellow[6];
	double r_cyan[6];
	double r_white[6];
	double r_black[6];
} registers_t;


typedef struct {
	registers_t r;
	u8 memory[MEM_SIZE];
} cpu_t;

cpu_t *new_cpu();
void free_cpu(cpu_t *cpu);

void dump_registers(cpu_t *cpu);

#endif