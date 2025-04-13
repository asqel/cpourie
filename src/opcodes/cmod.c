#include "cpu.h"

void handler_c8_cmod(cpu_t *cpu) {
	if (!can_acces_u8(cpu, cpu->r.r_pc + 1))
		return set_interrupt(cpu, CPU_INT_BADOPCODE);
	u8 info = get_u8(cpu, cpu->r.r_pc + 1);
	u32 A = get_Uregister_ptr(cpu, info >> 4);
	u32 B = get_Uregister_ptr(cpu, info & 0b1111);
	if (B == 0)
		return set_interrupt(cpu, CPU_INT_MOD_ZERO);
	update_status_mod(cpu, A, B);
	cpu->r.r_pc += 2;
}

void handler_c9_cmod(cpu_t *cpu) {
	if (!can_acces_u8(cpu, cpu->r.r_pc + 1))
		return set_interrupt(cpu, CPU_INT_BADOPCODE);
	u8 info = get_u8(cpu, cpu->r.r_pc + 1);
	if ((info & 0b11) != 0)
		return set_interrupt(cpu, CPU_INT_BADOPCODE);
	u8 TT = (info >> 2) & 0b11;
	if (!can_acces_u_with_size(cpu, cpu->r.r_pc + 2, TT))
		return set_interrupt(cpu, CPU_INT_BADOPCODE);
	u32 val = get_u_with_size(cpu, cpu->r.r_pc + 2, TT);
	if (val == 0)
		return set_interrupt(cpu, CPU_INT_MOD_ZERO);
	update_status_mod(cpu, *get_Uregister_ptr(cpu, info >> 4), val);
	cpu->r.r_pc += 2 + TYPE_SIZE(TT);
}