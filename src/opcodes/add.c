#include "cpu.h"

void handler_a0_add(cpu_t *cpu) {
	if (!can_acces_u8(cpu, cpu->r.r_pc + 1))
		return set_interrupt(cpu, CPU_INT_BADOPCODE);
	u8 info = get_u8(cpu, cpu->r.r_pc + 1);
	*get_Uregister_ptr(cpu, info >> 4) += *get_Uregister_ptr(cpu, info & 0b1111);
	cpu->r.r_pc += 2;
}

void handler_a1_add(cpu_t *cpu) {
	if (!can_acces_u8(cpu, cpu->r.r_pc + 1))
		return set_interrupt(cpu, CPU_INT_BADOPCODE);
	u8 info = get_u8(cpu, cpu->r.r_pc + 1);
	u8 TT = (info >> 2) & 0b11;
	if ((info & 0b11) != 0 || TT == 0b11)
		return set_interrupt(cpu, CPU_INT_BADOPCODE);
	if (!can_acces_u_with_size(cpu, cpu->r.r_pc + 2, TT))
		return set_interrupt(cpu, CPU_INT_BADOPCODE);
	*get_Uregister_ptr(cpu, info >> 4) += get_u_with_size(cpu, cpu->r.r_pc + 2, TT);
	cpu->r.r_pc += 2 + TYPE_SIZE(TT);
}

void handler_a2_add(cpu_t *cpu) {
	if (!can_acces_u8(cpu, cpu->r.r_pc + 1))
		return set_interrupt(cpu, CPU_INT_BADOPCODE);
	u8 info = get_u8(cpu, cpu->r.r_pc + 1);
	u32 *regA = get_Uregister_ptr(cpu, info >> 4);
	u32 *regB = get_Uregister_ptr(cpu, info & 0b1111);
	if (!can_acces_u32(cpu, *regB))
		return set_interrupt(cpu, CPU_INT_OUT_BOUND);
	*regA += get_u32(cpu, *regB);
	cpu->r.r_pc += 2;
}

void handler_a3_add(cpu_t *cpu) {
	if (!can_acces_u8(cpu, cpu->r.r_pc + 1))
		return set_interrupt(cpu, CPU_INT_BADOPCODE);
	u8 info = get_u8(cpu, cpu->r.r_pc + 1);
	u32 *regA = get_Uregister_ptr(cpu, info >> 4);
	u32 *regB = get_Uregister_ptr(cpu, info & 0b1111);
	if (!can_acces_u16(cpu, *regB))
		return set_interrupt(cpu, CPU_INT_OUT_BOUND);
	*regA += get_u16(cpu, *regB);
	cpu->r.r_pc += 2;
}

void handler_a4_add(cpu_t *cpu) {
	if (!can_acces_u8(cpu, cpu->r.r_pc + 1))
		return set_interrupt(cpu, CPU_INT_BADOPCODE);
	u8 info = get_u8(cpu, cpu->r.r_pc + 1);
	u32 *regA = get_Uregister_ptr(cpu, info >> 4);
	u32 *regB = get_Uregister_ptr(cpu, info & 0b1111);
	if (!can_acces_u8(cpu, *regB))
		return set_interrupt(cpu, CPU_INT_OUT_BOUND);
	*regA += get_u8(cpu, *regB);
	cpu->r.r_pc += 2;
}
