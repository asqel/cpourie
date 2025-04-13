#include "cpu.h"

void handler_6d_mov(cpu_t *cpu) {
	if (!can_acces_u8(cpu, cpu->r.r_pc + 1))
		return set_interrupt(cpu, CPU_INT_BADOPCODE);
	u8 info = get_u8(cpu, cpu->r.r_pc + 1);
	*get_Uregister_ptr(cpu, info >> 4) = *get_Uregister_ptr(cpu, info & 0b1111);
	cpu->r.r_pc += 2;
}

void handler_4d_mov(cpu_t *cpu) {
	if (!can_acces_u8(cpu, cpu->r.r_pc + 1))
		return set_interrupt(cpu, CPU_INT_BADOPCODE);
	u8 info = get_u8(cpu, cpu->r.r_pc + 1);
	u8 mod = info & 0b1111;
	u8 regA = info >> 4;

	if (mod == 0b0001)
		*get_Uregister_ptr(cpu, regA) = cpu->r.r_pc;
	else if (mod == 0b0010)
		*get_Uregister_ptr(cpu, regA) = cpu->r.r_status;
	else if (mod == 0b0011)
		cpu->r.r_status = *get_Uregister_ptr(cpu, regA);
	else
		return set_interrupt(cpu, CPU_INT_BADOPCODE);
	cpu->r.r_pc += 2;
}