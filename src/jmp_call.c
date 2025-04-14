#include "cpu.h"

int is_cond_true(cpu_t *cpu, u8 cond) {
	u32 status = cpu->r.r_status;

	switch (cond) {
		case CPU_COND_Uless: return (status >> 1) & 0b1;
		case CPU_COND_Ugreater: return (status >> 2) & 0b1;
		case CPU_COND_equal: return (status >> 3) & 0b1;
		case CPU_COND_Iless: return (status >> 4) & 0b1;
		case CPU_COND_Igreater: return (status >> 5) & 0b1;
		case CPU_COND_Uless_eq: return ((status >> 1) & 0b1) || (status >> 3) & 0b1;
		case CPU_COND_Ugreater_eq: return ((status >> 2) & 0b1) || (status >> 3) & 0b1;
		case CPU_COND_Iless_eq: return ((status >> 4) & 0b1) || (status >> 3) & 0b1;
		case CPU_COND_Igreater_eq: return ((status >> 5) & 0b1) || (status >> 3) & 0b1;
		case CPU_COND_True: return 1;
		case CPU_COND_mod0: return (status & 0b1) == 0;
		case CPU_COND_mod1: return (status & 0b1) == 1;
		default:
			return 2;
	}
}
// 2 :error cond, 0: no jumped, 1: jumped
int cpu_do_jump(cpu_t *cpu, u32 addr, u8 cond) {

	int ret = is_cond_true(cpu, cond);
	if (ret == 1)
		cpu->r.r_pc = addr;
	return ret;
}

// -1 outbound, 2: error cond, 0: no jumped, 1:jumped
int cpu_do_call(cpu_t *cpu, u32 addr, u8 cond, u32 ret_addr) {
	int ret = is_cond_true(cpu, cond);
	if (ret == 1) {
		if (cpu_push_u32(cpu, ret_addr) == -1)
			return (-1);
		cpu->r.r_pc = addr;
		return (1);
	}
	return ret;
}
