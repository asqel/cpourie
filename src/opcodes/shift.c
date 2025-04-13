#include "cpu.h"

void handler_34_ulshift(cpu_t *cpu) {
	if (!can_acces_u8(cpu, cpu->r.r_pc + 1))
		return set_interrupt(cpu, CPU_INT_BADOPCODE);
	u8 info = get_u8(cpu, cpu->r.r_pc + 1);
	*get_Uregister_ptr(cpu, info >> 4) <<= *get_Uregister_ptr(cpu, info & 0b1111);
	cpu->r.r_pc += 2;
}

void handler_35_ulshift(cpu_t *cpu) {
	if (!can_acces_u16(cpu, cpu->r.r_pc + 1))
		return set_interrupt(cpu, CPU_INT_BADOPCODE);
	u8 info = get_u8(cpu, cpu->r.r_pc + 1);
	if ((info & 0b1111) != 0)
		return set_interrupt(cpu, CPU_INT_BADOPCODE);
	*get_Uregister_ptr(cpu, info >> 4) <<= get_u8(cpu, cpu->r.r_pc + 2);
	cpu->r.r_pc += 3;
}

void handler_34_urshift(cpu_t *cpu) {
	if (!can_acces_u8(cpu, cpu->r.r_pc + 1))
		return set_interrupt(cpu, CPU_INT_BADOPCODE);
	u8 info = get_u8(cpu, cpu->r.r_pc + 1);
	*get_Uregister_ptr(cpu, info >> 4) >>= *get_Uregister_ptr(cpu, info & 0b1111);
	cpu->r.r_pc += 2;
}

void handler_35_urshift(cpu_t *cpu) {
	if (!can_acces_u16(cpu, cpu->r.r_pc + 1))
		return set_interrupt(cpu, CPU_INT_BADOPCODE);
	u8 info = get_u8(cpu, cpu->r.r_pc + 1);
	if ((info & 0b1111) != 0)
		return set_interrupt(cpu, CPU_INT_BADOPCODE);
	*get_Uregister_ptr(cpu, info >> 4) >>= get_u8(cpu, cpu->r.r_pc + 2);
	cpu->r.r_pc += 3;
}


