#include "cpu.h"
#include "opcodes.h"
#include "cpu_error.h"
#include "memory.h"

int do_ld_01_A(cpu_t *cpu) {
	if (!can_acces_u8(cpu, cpu->r.r_pc + 1))
		return set_error(err_phys_mem_not_present);
	if ((cpu->memory[cpu->r.r_pc + 1] & 0b11) == 0) {
		u8 size = cpu->memory[cpu->r.r_pc + 1] >> 6;
		if (!can_acces_u_with_size(cpu, cpu->r.r_pc + 2, size))
			return set_error(err_phys_mem_not_present);

		set_register(cpu, (cpu->memory[cpu->r.r_pc + 1] >> 2) & 0b1111, get_u_with_size(cpu, cpu->r.r_pc + 2, size));

		cpu->r.r_pc += SIZE(size) + 2;
		return set_error(err_none);
	}
	return -1;
}