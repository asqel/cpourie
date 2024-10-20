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

	switch (cpu->memory[cpu->r.r_pc]) {
		case OPC_push_u8_as_u8:
			if (cpu->r.r_sp - 1 >= cpu->mem_size || cpu->r.r_pc + 1 >= cpu->mem_size)
				return set_error(err_phys_mem_not_present);
			cpu->r.r_sp--;
			cpu->memory[cpu->r.r_sp] = INST_U8_PARAM(&cpu->memory[cpu->r.r_pc]);
			cpu->r.r_pc += 1 + SIZEOF_u8;
			return 0;

		case OPC_push_u8_as_u16:
			if (cpu->r.r_sp - 2 >= cpu->mem_size || cpu->r.r_pc + 1 >= cpu->mem_size)
				return set_error(err_phys_mem_not_present);
			cpu->r.r_sp--;
			cpu->memory[cpu->r.r_sp] = 0;
			cpu->r.r_sp--;
			cpu->memory[cpu->r.r_sp] = INST_U8_PARAM(&cpu->memory[cpu->r.r_pc]);
			cpu->r.r_pc += 1 + SIZEOF_u8;
			return 0;
		case OPC_push_u8_as_u32:
			if (cpu->r.r_sp - 4 >= cpu->mem_size || cpu->r.r_pc + 1 >= cpu->mem_size)
				return set_error(err_phys_mem_not_present);
			cpu->r.r_sp--;
			cpu->memory[cpu->r.r_sp] = 0;
			cpu->r.r_sp--;
			cpu->memory[cpu->r.r_sp] = 0;
			cpu->r.r_sp--;
			cpu->memory[cpu->r.r_sp] = 0;
			cpu->r.r_sp--;
			cpu->memory[cpu->r.r_sp] = INST_U8_PARAM(&cpu->memory[cpu->r.r_pc]);
			cpu->r.r_pc += 1 + SIZEOF_u8;
			return 0;
		case OPC_push_u8_as_u48:
			if (cpu->r.r_sp - 6 >= cpu->mem_size || cpu->r.r_pc + 1 >= cpu->mem_size)
				return set_error(err_phys_mem_not_present);
			cpu->r.r_sp--;
			cpu->memory[cpu->r.r_sp] = 0;
			cpu->r.r_sp--;
			cpu->memory[cpu->r.r_sp] = 0;
			cpu->r.r_sp--;
			cpu->memory[cpu->r.r_sp] = 0;
			cpu->r.r_sp--;
			cpu->memory[cpu->r.r_sp] = 0;
			cpu->r.r_sp--;
			cpu->memory[cpu->r.r_sp] = 0;
			cpu->r.r_sp--;
			cpu->memory[cpu->r.r_sp] = INST_U8_PARAM(&cpu->memory[cpu->r.r_pc]);
			cpu->r.r_pc += 1 + SIZEOF_u8;
			return 0;
		case OPC_push_u16_as_u16:
			if (cpu->r.r_sp - 2 >= cpu->mem_size || cpu->r.r_pc + 2 >= cpu->mem_size)
				return set_error(err_phys_mem_not_present);
			cpu->r.r_sp -= SIZEOF_u16;
			*((u16 *)&(cpu->memory[cpu->r.r_sp])) = INST_U16_PARAM(&cpu->memory[cpu->r.r_pc]);
			cpu->r.r_pc += 1 + SIZEOF_u16;
			return 0;
		case OPC_push_u16_as_u32:
			if (cpu->r.r_sp - 4 >= cpu->mem_size || cpu->r.r_pc + 2 >= cpu->mem_size)
				return set_error(err_phys_mem_not_present);
			cpu->r.r_sp--;
			cpu->memory[cpu->r.r_sp] = 0;
			cpu->r.r_sp--;
			cpu->memory[cpu->r.r_sp] = 0;
			cpu->r.r_sp -= SIZEOF_u16;
			*((u16 *)&(cpu->memory[cpu->r.r_sp])) = INST_U16_PARAM(&cpu->memory[cpu->r.r_pc]);
			cpu->r.r_pc += 1 + SIZEOF_u16;
			return 0;
		case OPC_push_u16_as_u48:
			if (cpu->r.r_sp - 6 >= cpu->mem_size || cpu->r.r_pc + 2 >= cpu->mem_size)
				return set_error(err_phys_mem_not_present);
			cpu->r.r_sp--;
			cpu->memory[cpu->r.r_sp] = 0;
			cpu->r.r_sp--;
			cpu->memory[cpu->r.r_sp] = 0;
			cpu->r.r_sp--;
			cpu->memory[cpu->r.r_sp] = 0;
			cpu->r.r_sp--;
			cpu->memory[cpu->r.r_sp] = 0;
			cpu->r.r_sp -= SIZEOF_u16;
			*((u16 *)&(cpu->memory[cpu->r.r_sp])) = INST_U16_PARAM(&cpu->memory[cpu->r.r_pc]);
			cpu->r.r_pc += 1 + SIZEOF_u16;
			return 0;
		case OPC_push_u32_as_u32:
			if (cpu->r.r_sp - 4 >= cpu->mem_size || cpu->r.r_pc + 4 >= cpu->mem_size)
				return set_error(err_phys_mem_not_present);
			cpu->r.r_sp -= SIZEOF_u32;
			*((u32 *)&(cpu->memory[cpu->r.r_sp])) = INST_U32_PARAM(&cpu->memory[cpu->r.r_pc]);
			cpu->r.r_pc += 1 + SIZEOF_u32;
			return 0;
		case OPC_push_u32_as_u48:
			if (cpu->r.r_sp - 6 >= cpu->mem_size || cpu->r.r_pc + 4 >= cpu->mem_size)
				return set_error(err_phys_mem_not_present);
			cpu->r.r_sp--;
			cpu->memory[cpu->r.r_sp] = 0;
			cpu->r.r_sp -= SIZEOF_u32;
			*((u32 *)&(cpu->memory[cpu->r.r_sp])) = INST_U32_PARAM(&cpu->memory[cpu->r.r_pc]);
			cpu->r.r_pc += 1 + SIZEOF_u32;
			return 0;
		case OPC_push_u48_as_u48:
			if (cpu->r.r_sp - 6 >= cpu->mem_size || cpu->r.r_pc + 6 >= cpu->mem_size)
				return set_error(err_phys_mem_not_present);
			cpu->r.r_sp -= SIZEOF_u48;
			for(int i = 0; i < SIZEOF_u48; i++)
				cpu->memory[cpu->r.r_sp + i] = cpu->memory[cpu->r.r_pc + i];
			cpu->r.r_pc += 1 + SIZEOF_u48;
			return 0;
		case OPC_push_double:
			if (cpu->r.r_sp - 8 >= cpu->mem_size || cpu->r.r_pc + 8 >= cpu->mem_size)
				return set_error(err_phys_mem_not_present);
			cpu->r.r_sp -= SIZEOF_fpoint;
			for(int i = 0; i < SIZEOF_fpoint; i++)
				cpu->memory[cpu->r.r_sp + i] = cpu->memory[cpu->r.r_pc + i];
			cpu->r.r_pc += 1 + SIZEOF_fpoint;
			return 0;
		default:
			break;
	}
	int temp = do_opcode_mov(cpu);
	if (temp != -1)
		return temp;
	
	return err_bad_opcode;
}