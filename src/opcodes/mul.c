#include "cpu.h"

void handler_b0_imul(cpu_t *cpu) {
	if (!can_acces_u8(cpu, cpu->r.r_pc + 1))
		return set_interrupt(cpu, CPU_INT_BADOPCODE);
	u8 info = get_u8(cpu, cpu->r.r_pc + 1);
	*get_Iregister_ptr(cpu, info >> 4) *= *get_Iregister_ptr(cpu, info & 0b1111);
	cpu->r.r_pc += 2;
}

void handler_b1_imul(cpu_t *cpu) {
	if (!can_acces_u8(cpu, cpu->r.r_pc + 1))
		return set_interrupt(cpu, CPU_INT_BADOPCODE);
	u8 info = get_u8(cpu, cpu->r.r_pc + 1);
	if ((info & 0b11) != 0)
		return set_interrupt(cpu, CPU_INT_BADOPCODE);
	u8 TT = (info >> 2) & 0b11;
	if (TT == 0b11)
		return set_interrupt(cpu, CPU_INT_BADOPCODE);
	*get_Iregister_ptr(cpu, info >> 4) *= get_i_with_size(cpu, cpu->r.r_pc + 2, TT);
	cpu->r.r_pc += 2 + TYPE_SIZE(TT);
}

void handler_b2_umul(cpu_t *cpu) {
	if (!can_acces_u8(cpu, cpu->r.r_pc + 1))
		return set_interrupt(cpu, CPU_INT_BADOPCODE);
	u8 info = get_u8(cpu, cpu->r.r_pc + 1);
	*get_Uregister_ptr(cpu, info >> 4) *= *get_Uregister_ptr(cpu, info & 0b1111);
	cpu->r.r_pc += 2;
}

void handler_b3_umul(cpu_t *cpu) {
	if (!can_acces_u8(cpu, cpu->r.r_pc + 1))
		return set_interrupt(cpu, CPU_INT_BADOPCODE);
	u8 info = get_u8(cpu, cpu->r.r_pc + 1);
	if ((info & 0b11) != 0)
		return set_interrupt(cpu, CPU_INT_BADOPCODE);
	u8 TT = (info >> 2) & 0b11;
	if (TT == 0b11)
		return set_interrupt(cpu, CPU_INT_BADOPCODE);
	*get_Uregister_ptr(cpu, info >> 4) *= get_u_with_size(cpu, cpu->r.r_pc + 2, TT);
	cpu->r.r_pc += 2 + TYPE_SIZE(TT);
}
