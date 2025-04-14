#include "cpu.h"

int cpu_push_u32(cpu_t *cpu, u32 val) {
	cpu->r.r_sp -= 4;
	if (!can_acces_u32(cpu, cpu->r.r_sp))
		return (-1);
	set_u32(cpu, cpu->r.r_sp, val);
	return (0);
}

int cpu_push_u16(cpu_t *cpu, u16 val) {
	cpu->r.r_sp -= 2;
	if (!can_acces_u16(cpu, cpu->r.r_sp))
		return (-1);
	set_u16(cpu, cpu->r.r_sp, val);
	return (0);
}

int cpu_push_u8(cpu_t *cpu, u8 val) {
	cpu->r.r_sp -= 1;
	if (!can_acces_u8(cpu, cpu->r.r_sp))
		return (-1);
	set_u8(cpu, cpu->r.r_sp, val);
	return (0);
}

int cpu_push_u_with_size(cpu_t *cpu, u32 val, u8 type) {
	switch (type) {
		case 0b00:
			return cpu_push_u8(cpu, val);
		case 0b01:
			return cpu_push_u16(cpu, val);
		case 0b10:
			return cpu_push_u32(cpu, val);
		default : break;
	}
	printf("Error cpu wrong size in cpu_push_with_size\n");
	exit(1);
}