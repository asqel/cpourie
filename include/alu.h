#ifndef ALU_H
#define ALU_H

#include "cpu.h"

void alu_add_unsigned(cpu_t *cpu, u8 regA, u8 regB, u8 regOUT);
void alu_add_signed(cpu_t *cpu, u8 regA, u8 regB, u8 regOUT);
void alu_sub_unsigned(cpu_t *cpu, u8 regA, u8 regB, u8 regOUT);
void alu_sub_signed(cpu_t *cpu, u8 regA, u8 regB, u8 regOUT);
void alu_mul_unsigned(cpu_t *cpu, u8 regA, u8 regB, u8 regOUT);
void alu_mul_signed(cpu_t *cpu, u8 regA, u8 regB, u8 regOUT);

#endif