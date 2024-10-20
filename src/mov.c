#include "cpu.h"
#include "opcodes.h"
#include "cpu_error.h"

/*
0: instruction done
1: error
-1: no instruction find go next
*/

int do_opcode_mov(cpu_t *cpu) {
	u8 opcode = cpu->memory[cpu->r.r_pc];
	// 0b01111XXX
	if (opcode & 0b01111000) {
		if (cpu->r.r_pc + 1 >= cpu->mem_size)
			return set_error(err_phys_mem_not_present);
		u8 reg = opcode & 0b00000111;
		if (reg == 0b111)
			return set_error(err_bad_opcode);
		u8 idx =  cpu->memory[cpu->r.r_pc + 1] & 0b11;
		u8 size = (cpu->memory[cpu->r.r_pc + 1] & 0b1100) >> 2;
		switch (size) {
			case 0b00:
				size = 1;
				break;
			case 0b01:
				size = 2;
				break;
			case 0b10:
				size = 4;
				break;
			case 0b11:
				size = 6;
				break;
			default:
				break;
		}
		if (cpu->r.r_pc + 1 + size >= cpu->mem_size)
			return set_error(err_phys_mem_not_present);
		u8 *reg_ptr = (u8 *)&cpu->r.r_do[1];
		switch (reg) {
			case 0b000:
				reg_ptr = (u8 *)&(cpu->r.r_do[idx]); break;
			case 0b001:
				reg_ptr = (u8 *)&(cpu->r.r_re[idx]); break;
			case 0b010:
				reg_ptr = (u8 *)&(cpu->r.r_mi[idx]); break;
			case 0b011:
				reg_ptr = (u8 *)&(cpu->r.r_fa[idx]); break;
			case 0b100:
				reg_ptr = (u8 *)&(cpu->r.r_so[idx]); break;
			case 0b101:
				reg_ptr = (u8 *)&(cpu->r.r_la[idx]); break;
			case 0b110:
				reg_ptr = (u8 *)&(cpu->r.r_si[idx]); break;
			default:
				break;
		}
		for (int i = 0; i < 6; i++)
			reg_ptr[i] = 0;
		for (int i = 0; i < size; i++) {
			reg_ptr[i] = cpu->memory[cpu->r.r_pc + 2 + i];
		}
	}
	return -1;
}