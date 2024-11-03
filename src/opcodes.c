#include "cpu.h"
#include "opcodes.h"
#include "cpu_error.h"

//int do_opcode(cpu_t *cpu) {
//
//		case OPC_mov_u48_do0:
//		case OPC_mov_u48_do1:
//		case OPC_mov_u48_do2:
//		case OPC_mov_u48_do3:
//			for(int i = 0; i < SIZEOF_u48; i++) {
//				cpu->r.r_do[cpu->memory[cpu->r.r_pc] & 0b11]
//			}
//			cpu->r.r_pc += 1 + SIZEOF_u48;
//			break;
//		case OPC_mov_u48_re0:
//		case OPC_mov_u48_re1:
//		case OPC_mov_u48_re2:
//		case OPC_mov_u48_re3:
//
//		case OPC_mov_u48_mi0:
//		case OPC_mov_u48_mi1:
//		case OPC_mov_u48_mi2:
//		case OPC_mov_u48_mi3:
//
//		case OPC_mov_u48_fa0:
//		case OPC_mov_u48_fa1:
//		case OPC_mov_u48_fa2:
//		case OPC_mov_u48_fa3:
//
//		case OPC_mov_u48_so0:
//		case OPC_mov_u48_so1:
//		case OPC_mov_u48_so2:
//		case OPC_mov_u48_so3:
//
//		case OPC_mov_u48_la0:
//		case OPC_mov_u48_la1:
//		case OPC_mov_u48_la2:
//		case OPC_mov_u48_la3:
//
//		case OPC_mov_u48_si0:
//		case OPC_mov_u48_si1:
//		case OPC_mov_u48_si2:
//		case OPC_mov_u48_si3:
//		default:
//			return 1;
//	}
//	return 0;
//}

int do_opcode(cpu_t *cpu) {
	if (cpu->r.r_pc >= cpu->mem_size)
		return set_error(err_phys_mem_not_present);

	u8 infos;
	switch (cpu->memory[cpu->r.r_pc]) {
		case 0b00000001:
			if (cpu->r.r_pc + 1 >= cpu->mem_size)
				return set_error(err_phys_mem_not_present);
			infos = cpu->memory[cpu->r.r_pc + 1];
			if (infos >> 4 == 0) {
				u8 v_size = infos >> 2;
				u8 cast_size = infos & 0b11;
				if (v_size > cast_size)
					return set_error(err_bad_opcode);
				switch (v_size) {
					case 0b00: v_size = 1;break;
					case 0b01: v_size = 2;break;
					case 0b10: v_size = 4;break;
					case 0b11: v_size = 6;break;
					default: break;
				}
				switch (cast_size) {
					case 0b00: cast_size = 1;break;
					case 0b01: cast_size = 2;break;
					case 0b10: cast_size = 4;break;
					case 0b11: cast_size = 6;break;
					default: break;
				}
				if (cpu->r.r_pc + 1 + v_size >= cpu->mem_size)
					return set_error(err_phys_mem_not_present);
				if (cpu->r.r_sp - cast_size >= cpu->mem_size || cpu->r.r_sp >= cpu->mem_size)
					return set_error(err_phys_mem_not_present);

				cpu->r.r_sp -= cast_size;
				for (int i = 0; i < cast_size; i++)
					cpu->memory[cpu->r.r_sp + i] = 0;
				for (int i = 0; i < v_size; i++)
					cpu->memory[cpu->r.r_sp + i] = cpu->memory[cpu->r.r_pc + 2 + i];
				cpu->r.r_pc += 2 + v_size;
				return set_error(err_none);
			}
			else if (infos >> 7 == 1) {
				u8 reg_num = infos & 0b111;
				if (reg_num == 0b111)
					return set_error(err_bad_opcode);
				u8 reg_idx = (infos >> 3) & 0b11;
				u8 cast_size = (infos >> 5) & 0b11;
				u48 *value;
				switch (reg_num) {
					case 0b000: value = &(cpu->r.r_do[reg_idx]); break;
					case 0b001: value = &(cpu->r.r_re[reg_idx]); break;
					case 0b010: value = &(cpu->r.r_mi[reg_idx]); break;
					case 0b011: value = &(cpu->r.r_fa[reg_idx]); break;
					case 0b100: value = &(cpu->r.r_so[reg_idx]); break;
					case 0b101: value = &(cpu->r.r_la[reg_idx]); break;
					case 0b110: value = &(cpu->r.r_si[reg_idx]); break;
				}
				if (cpu->r.r_sp - cast_size >= cpu->mem_size || cpu->r.r_sp >= cpu->mem_size)
					return set_error(err_phys_mem_not_present);
				cpu->r.r_sp -= cast_size;
				for (int i = 0; i < cast_size; i++)
					cpu->memory[cpu->r.r_sp + i] = value[i];
				cpu->r.r_pc += 2;
				return set_error(err_none);
			}
			else if (infos >> 6 == 0b01) {
				if (cpu->r.r_sp - SIZEOF_fpoint >= cpu->mem_size || cpu->r.r_sp >= cpu->mem_size) {
					return set_error(err_phys_mem_not_present);
				}
				u8 reg_num = infos & 0b111;
				u8 reg_idx = (infos >> 3) & 0b111;
				fpoint *value;
				switch (reg_num) {
					case 0b000: value = &(cpu->r.r_red[reg_idx]); break;
					case 0b001: value = &(cpu->r.r_green[reg_idx]); break;
					case 0b010: value = &(cpu->r.r_blue[reg_idx]); break;
					case 0b011: value = &(cpu->r.r_magenta[reg_idx]); break;
					case 0b100: value = &(cpu->r.r_yellow[reg_idx]); break;
					case 0b101: value = &(cpu->r.r_cyan[reg_idx]); break;
					case 0b110: value = &(cpu->r.r_white[reg_idx]); break;
					case 0b111: value = &(cpu->r.r_black[reg_idx]); break;
				}
				cpu->r.r_sp -= SIZEOF_fpoint;
				for (int i = 0; i < 4; i++)
					cpu->memory[cpu->r.r_sp + i] = ((u8 *)(value->int_part))[i];
				for (int i = 0; i < 4; i++)
					cpu->memory[cpu->r.r_sp + i + 4] = ((u8 *)(value->dec_part))[i];
				cpu->r.r_pc += 2;
				return set_error(err_none);
			}
			else {
				return set_error(err_bad_opcode);
			}
		case 0b00000010:
			if (cpu->r.r_pc + SIZEOF_fpoint >= cpu->mem_size)
				return set_error(err_phys_mem_not_present);
			if (cpu->r.r_sp - SIZEOF_fpoint >= cpu->mem_size || cpu->r.r_sp >= cpu->mem_size)
				return set_error(err_phys_mem_not_present);
			cpu->r.r_sp -= SIZEOF_fpoint;
			for (int i = 0; i < SIZEOF_fpoint; i++)
				cpu->memory[cpu->r.r_sp + i] = cpu->memory[cpu->r.r_pc + i + 1];
			cpu->r.r_pc += 1 + SIZEOF_fpoint;
			return set_error(err_none);
		case 0b00000011:
			if (cpu->r.r_pc + 1 >= cpu->mem_size)
				return set_error(err_phys_mem_not_present);
			
		default:
			break;
	}
	
	return set_error(err_bad_opcode);
}