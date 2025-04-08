#ifndef OPCODES_H
#define OPCODES_H

#include "cpu.h"

void init_opcodes();

#define SIZE(X) (((int []){1, 2, 4, 6})[X])

int do_opcode(cpu_t *cpu);
int do_opcode_mov(cpu_t *cpu);

int do_ld_01_A(cpu_t *cpu);

#endif