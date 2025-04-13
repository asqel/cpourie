#include "cpu.h"

void handler_20_band(cpu_t *cpu) {
	if (!can_acces_u8(cpu, cpu->r.r_pc + 1))
		return set_interrupt(cpu, CPU_INT_BADOPCODE);
	u8 info = get_u8(cpu, cpu->r.r_pc + 1);
	*get_Uregister_ptr(cpu, info >> 4) &= *get_Uregister_ptr(cpu, info & 0b1111);
	cpu->r.r_pc += 2;
}

void handler_21_band(cpu_t *cpu) {
	if (!can_acces_u8(cpu, cpu->r.r_pc + 1))
		return set_interrupt(cpu, CPU_INT_BADOPCODE);
	u8 info = get_u8(cpu, cpu->r.r_pc + 1);
	if ((info & 0b11) != 0)
		return set_interrupt(cpu, CPU_INT_BADOPCODE);
	u8 TT = (info >> 2) & 0b11;
	if (TT == 0b11)
		return set_interrupt(cpu, CPU_INT_BADOPCODE);
	if (!can_acces_u_with_size(cpu, cpu->r.r_pc + 2, TT))
		return set_interrupt(cpu, CPU_INT_BADOPCODE);
	*get_Uregister_ptr(cpu, info >> 4) &= get_u_with_size(cpu, cpu->r.r_pc + 2, TT);
	cpu->r.r_pc += 2 + TYPE_SIZE(TT);
}

void handler_22_bor(cpu_t *cpu) {
	if (!can_acces_u8(cpu, cpu->r.r_pc + 1))
		return set_interrupt(cpu, CPU_INT_BADOPCODE);
	u8 info = get_u8(cpu, cpu->r.r_pc + 1);
	*get_Uregister_ptr(cpu, info >> 4) |= *get_Uregister_ptr(cpu, info & 0b1111);
	cpu->r.r_pc += 2;
}

void handler_23_bor(cpu_t *cpu) {
	if (!can_acces_u8(cpu, cpu->r.r_pc + 1))
		return set_interrupt(cpu, CPU_INT_BADOPCODE);
	u8 info = get_u8(cpu, cpu->r.r_pc + 1);
	if ((info & 0b11) != 0)
		return set_interrupt(cpu, CPU_INT_BADOPCODE);
	u8 TT = (info >> 2) & 0b11;
	if (TT == 0b11)
		return set_interrupt(cpu, CPU_INT_BADOPCODE);
	if (!can_acces_u_with_size(cpu, cpu->r.r_pc + 2, TT))
		return set_interrupt(cpu, CPU_INT_BADOPCODE);
	*get_Uregister_ptr(cpu, info >> 4) |= get_u_with_size(cpu, cpu->r.r_pc + 2, TT);
	cpu->r.r_pc += 2 + TYPE_SIZE(TT);
}

void handler_24_not(cpu_t *cpu) {
	if (!can_acces_u8(cpu, cpu->r.r_pc + 1))
		return set_interrupt(cpu, CPU_INT_BADOPCODE);
	u8 info = get_u8(cpu, cpu->r.r_pc + 1);
	if ((info & 0b1111) != 0)
		return set_interrupt(cpu, CPU_INT_BADOPCODE);
	u32 *reg = get_Uregister_ptr(cpu, info >> 4);
	*reg = ~*reg;
	cpu->r.r_pc += 2;
}


void handler_25_bxor(cpu_t *cpu) {
	if (!can_acces_u8(cpu, cpu->r.r_pc + 1))
		return set_interrupt(cpu, CPU_INT_BADOPCODE);
	u8 info = get_u8(cpu, cpu->r.r_pc + 1);
	*get_Uregister_ptr(cpu, info >> 4) ^= *get_Uregister_ptr(cpu, info & 0b1111);
	cpu->r.r_pc += 2;
}

void handler_26_bxor(cpu_t *cpu) {
	if (!can_acces_u8(cpu, cpu->r.r_pc + 1))
		return set_interrupt(cpu, CPU_INT_BADOPCODE);
	u8 info = get_u8(cpu, cpu->r.r_pc + 1);
	if ((info & 0b11) != 0)
		return set_interrupt(cpu, CPU_INT_BADOPCODE);
	u8 TT = (info >> 2) & 0b11;
	if (TT == 0b11)
		return set_interrupt(cpu, CPU_INT_BADOPCODE);
	if (!can_acces_u_with_size(cpu, cpu->r.r_pc + 2, TT))
		return set_interrupt(cpu, CPU_INT_BADOPCODE);
	*get_Uregister_ptr(cpu, info >> 4) ^= get_u_with_size(cpu, cpu->r.r_pc + 2, TT);
	cpu->r.r_pc += 2 + TYPE_SIZE(TT);
}
