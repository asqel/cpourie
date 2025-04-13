#include "cpu.h"

void handler_30_land(cpu_t *cpu) {
	if (!can_acces_u8(cpu, cpu->r.r_pc + 1))
		return set_interrupt(cpu, CPU_INT_BADOPCODE);
	u8 info = get_u8(cpu, cpu->r.r_pc + 1);
	u32 *reg = get_Uregister_ptr(cpu, info >> 4);
	*reg = (*reg) && (*get_Uregister_ptr(cpu, info & 0b1111));
	cpu->r.r_pc += 2;
}

void handler_31_lor(cpu_t *cpu) {
	if (!can_acces_u8(cpu, cpu->r.r_pc + 1))
		return set_interrupt(cpu, CPU_INT_BADOPCODE);
	u8 info = get_u8(cpu, cpu->r.r_pc + 1);
	u32 *reg = get_Uregister_ptr(cpu, info >> 4);
	*reg = (*reg) || (*get_Uregister_ptr(cpu, info & 0b1111));
	cpu->r.r_pc += 2;
}

void handler_32_lnot(cpu_t *cpu) {
	if (!can_acces_u8(cpu, cpu->r.r_pc + 1))
		return set_interrupt(cpu, CPU_INT_BADOPCODE);
	u8 info = get_u8(cpu, cpu->r.r_pc + 1);
	if ((info & 0b1111) != 0)
		return set_interrupt(cpu, CPU_INT_BADOPCODE);
	u32 *reg = get_Uregister_ptr(cpu, info >> 4);
	*reg = !(*reg);
}

void handler_33_land(cpu_t *cpu) {
	if (!can_acces_u8(cpu, cpu->r.r_pc + 1))
		return set_interrupt(cpu, CPU_INT_BADOPCODE);
	u8 info = get_u8(cpu, cpu->r.r_pc + 1);
	u32 *reg = get_Uregister_ptr(cpu, info >> 4);
	u32 *reg2 = get_Uregister_ptr(cpu, info & 0b1111);
	u32 a = *reg;
	u32 b = *reg2;
	*reg = (!a && b) || (a && !b);
	cpu->r.r_pc += 2;
}
