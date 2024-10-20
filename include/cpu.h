#ifndef CPU_H
#define CPU_H

#include "types.h"

typedef struct {
	u48 r_do[4];
	u48 r_re[4];
	u48 r_mi[4];
	u48 r_fa[4];
	u48 r_so[4];
	u48 r_la[4];
	u48 r_si[4];

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
	u8 *memory;
	u48 mem_size;
} cpu_t;

cpu_t *new_cpu(u48 mem_size);
void free_cpu(cpu_t *cpu);

void dump_registers(cpu_t *cpu);

#endif