#include "cpu.h"

void handler_8f_ret(cpu_t *cpu) {
	if (!can_acces_u32(cpu, cpu->r.r_sp))
		return set_interrupt(cpu, CPU_INT_OUT_BOUND);
	cpu->r.r_pc = get_u32(cpu, cpu->r.r_sp);
	cpu->r.r_sp += 4;
}

void handler_f4_sret(cpu_t *cpu) {
	if (cpu->r.level != CPU_LV_K)
		return set_interrupt(cpu, CPU_INT_PRIVILEGE);
	if (cpu_pop_level(cpu) == -1)
		return set_interrupt(cpu, CPU_INT_OUT_BOUND);
	if (!can_acces_u32(cpu, cpu->r.r_sp))
		return set_interrupt(cpu, CPU_INT_OUT_BOUND);
	cpu->r.r_pc = get_u32(cpu, cpu->r.r_sp);
	cpu->r.r_sp += 4;
}

void handler_f4_dret(cpu_t *cpu) {
	if (cpu->r.level != CPU_LV_D)
		return set_interrupt(cpu, CPU_INT_PRIVILEGE);
	if (cpu_pop_level(cpu) == -1)
		return set_interrupt(cpu, CPU_INT_OUT_BOUND);
	if (!can_acces_u32(cpu, cpu->r.r_sp))
		return set_interrupt(cpu, CPU_INT_OUT_BOUND);
	cpu->r.r_pc = get_u32(cpu, cpu->r.r_sp);
	cpu->r.r_sp += 4;
}
