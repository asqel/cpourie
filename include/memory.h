#ifndef MEMORY_H
#define MEMORY_H

#include "cpu.h"
#include "types.h"

int can_acces_u8(cpu_t *cpu, u32 addr);
int can_acces_u16(cpu_t *cpu, u32 addr);
int can_acces_u32(cpu_t *cpu, u32 addr);
int can_acces_u32(cpu_t *cpu, u32 addr);
u32 get_u8(cpu_t *cpu, u32 addr);
u32 get_u16(cpu_t *cpu, u32 addr);
u32 get_u32(cpu_t *cpu, u32 addr);
u32 get_u32(cpu_t *cpu, u32 addr);
u32 get_u_with_size(cpu_t *cpu, u32 addr, u8 size);
int can_acces_u_with_size(cpu_t *cpu, u32 addr, u8 size);

#endif