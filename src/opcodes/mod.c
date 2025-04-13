#include "cpu.h"

void handler_b6_imod(cpu_t *cpu) {
	if (!can_acces_u8(cpu, cpu->r.r_pc + 1))
		return set_interrupt(cpu, CPU_INT_BADOPCODE);
	u8 info = get_u8(cpu, cpu->r.r_pc + 1);
	i32 *B = get_Iregister_ptr(cpu, info & 0b1111);
	if (*B == 0)
		return set_interrupt(cpu, CPU_INT_MOD_ZERO);
	i32 *A = get_Iregister_ptr(cpu, info >> 4);
	*A = (*A) / (*B);
	cpu->r.r_pc += 2;
}

void handler_b7_umod(cpu_t *cpu) {
	if (!can_acces_u8(cpu, cpu->r.r_pc + 1))
		return set_interrupt(cpu, CPU_INT_BADOPCODE);
	u8 info = get_u8(cpu, cpu->r.r_pc + 1);
	u32 *B = get_Uregister_ptr(cpu, info & 0b1111);
	if (*B == 0)
		return set_interrupt(cpu, CPU_INT_MOD_ZERO);
	u32 *A = get_Uregister_ptr(cpu, info >> 4);
	*A = (*A) / (*B);
	cpu->r.r_pc += 2;
}
