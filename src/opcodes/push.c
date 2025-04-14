#include "cpu.h"

void handler_e2_push(cpu_t *cpu) {
	if (!can_acces_u8(cpu, cpu->r.r_pc + 1))
		return set_interrupt(cpu, CPU_INT_BADOPCODE);
	u8 info = get_u8(cpu, cpu->r.r_pc + 1);

	u8 mod = info & 0b11;
	u8 TT = (info >> 2) & 0b11;
	u8 reg = info >> 4;

	if (mod == 0b00) {
		if (cpu_push_u_with_size(cpu, *get_Uregister_ptr(cpu, reg), TT) == -1)
			return set_interrupt(cpu, CPU_INT_OUT_BOUND);
		cpu->r.r_pc += 2;
		return ;
	}
	if (mod == 0b11 && reg == 0) {
		if (!can_acces_u_with_size(cpu, cpu->r.r_pc + 2, TT))
			return set_interrupt(cpu, CPU_INT_BADOPCODE);
		if (cpu_push_u_with_size(cpu, get_u_with_size(cpu, cpu->r.r_pc + 2, TT), TT) == -1)
			return set_interrupt(cpu, CPU_INT_OUT_BOUND);
		cpu->r.r_pc += 2 + TYPE_SIZE(TT);
		return ;
	}
	if (mod == 0b10) {
		u32 reg_content = *get_Uregister_ptr(cpu, reg);
		if (!can_acces_u_with_size(cpu, reg_content, TT))
			return set_interrupt(cpu, CPU_INT_OUT_BOUND);
		u32 to_push = get_u_with_size(cpu, reg_content, TT);
		if (cpu_push_u_with_size(cpu, to_push, TT) == -1)
			return set_interrupt(cpu, CPU_INT_OUT_BOUND);
		cpu->r.r_pc += 2;
		return ;
	}
	return set_interrupt(cpu, CPU_INT_BADOPCODE);
}