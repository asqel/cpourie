#include "cpu.h"

void handler_d0_swap(cpu_t *cpu) {
	if (!can_acces_u8(cpu, cpu->r.r_pc + 1))
		return set_interrupt(cpu, CPU_INT_BADOPCODE);
	u8 info = get_u8(cpu, cpu->r.r_pc + 1);

	u32 *regA = get_Uregister_ptr(cpu, info >> 4);
	u32 *regB = get_Uregister_ptr(cpu, info & 0b1111);
	u32 tmp = 0;

	tmp = *regA;
	regB = *regA;
	*regA = tmp;
	cpu->r.r_pc += 2;
}