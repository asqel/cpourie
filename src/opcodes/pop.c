#include "cpu.h"

void handler_e8_pop(cpu_t *cpu) {
	if (!can_acces_u8(cpu, cpu->r.r_pc + 1))
		return set_interrupt(cpu, CPU_INT_BADOPCODE);
	u8 info = get_u8(cpu, cpu->r.r_pc + 1);

	u8 mod = info & 0b11;
	u8 TT = (info >> 2) & 0b11;
	u8 reg = info >> 4;
	if (mod == 0b00) {
		if (!can_acces_u_with_size(cpu, cpu->r.r_sp, TT))
			return set_interrupt(cpu, CPU_INT_OUT_BOUND);
		*get_Uregister_ptr(cpu, reg) = get_u_with_size(cpu, cpu->r.r_sp, TT);
		cpu->r.r_pc += 2;
		cpu->r.r_sp += TYPE_SIZE(TT);
		return ;
	}
	if (mod == 0b11) {
		if (!can_acces_u_with_size(cpu, cpu->r.r_sp, TT))
			return set_interrupt(cpu, CPU_INT_OUT_BOUND);
		u32 addr = *get_Uregister_ptr(cpu, reg);
		if (!can_acces_u_with_size(cpu, addr, TT))
			return set_interrupt(cpu, CPU_INT_OUT_BOUND);
		set_u_with_size(cpu, addr, TT, get_u_with_size(cpu, cpu->r.r_sp, TT));
		cpu->r.r_pc += 2;
		cpu->r.r_sp += TYPE_SIZE(TT);
		return ;
	}
	return set_interrupt(cpu, CPU_INT_BADOPCODE);

}