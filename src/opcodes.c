#include "cpu.h"
#include "opcodes.h"

int do_opcode(cpu_t *cpu) {
	switch (cpu->memory[cpu->r.r_pc]) {
		case OPC_push_u8_as_u8:
			cpu->r.r_sp--;
			cpu->memory[cpu->r.r_sp] = INST_U8_PARAM(&cpu->memory[cpu->r.r_pc]);
			cpu->r.r_pc += 1 + SIZEOF_u8;
			break;
		case OPC_push_u8_as_u16:
			cpu->r.r_sp--;
			cpu->memory[cpu->r.r_sp] = 0;
			cpu->r.r_sp--;
			cpu->memory[cpu->r.r_sp] = INST_U8_PARAM(&cpu->memory[cpu->r.r_pc]);
			cpu->r.r_pc += 1 + SIZEOF_u8;
			break;
		case OPC_push_u8_as_u32:
			cpu->r.r_sp--;
			cpu->memory[cpu->r.r_sp] = 0;
			cpu->r.r_sp--;
			cpu->memory[cpu->r.r_sp] = 0;
			cpu->r.r_sp--;
			cpu->memory[cpu->r.r_sp] = 0;
			cpu->r.r_sp--;
			cpu->memory[cpu->r.r_sp] = INST_U8_PARAM(&cpu->memory[cpu->r.r_pc]);
			cpu->r.r_pc += 1 + SIZEOF_u8;
			break;
		case OPC_push_u8_as_u48:
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
			break;
		case OPC_push_u16_as_u16:
			cpu->r.r_sp -= SIZEOF_u16;
			*((u16 *)&(cpu->memory[cpu->r.r_sp])) = INST_U16_PARAM(&cpu->memory[cpu->r.r_pc]);
			cpu->r.r_pc += 1 + SIZEOF_u16;
			break;
		case OPC_push_u16_as_u32:
			cpu->r.r_sp--;
			cpu->memory[cpu->r.r_sp] = 0;
			cpu->r.r_sp--;
			cpu->memory[cpu->r.r_sp] = 0;
			cpu->r.r_sp -= SIZEOF_u16;
			*((u16 *)&(cpu->memory[cpu->r.r_sp])) = INST_U16_PARAM(&cpu->memory[cpu->r.r_pc]);
			cpu->r.r_pc += 1 + SIZEOF_u16;
			break;
		case OPC_push_u16_as_u48:
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
			break;
		case OPC_push_u32_as_u32:
			cpu->r.r_sp -= SIZEOF_u32;
			*((u32 *)&(cpu->memory[cpu->r.r_sp])) = INST_U32_PARAM(&cpu->memory[cpu->r.r_pc]);
			cpu->r.r_pc += 1 + SIZEOF_u32;
			break;
		case OPC_push_u32_as_u48:
			cpu->r.r_sp--;
			cpu->memory[cpu->r.r_sp] = 0;
			cpu->r.r_sp -= SIZEOF_u32;
			*((u32 *)&(cpu->memory[cpu->r.r_sp])) = INST_U32_PARAM(&cpu->memory[cpu->r.r_pc]);
			cpu->r.r_pc += 1 + SIZEOF_u32;
			break;
		case OPC_push_u48_as_u48:
			cpu->r.r_sp -= SIZEOF_u48;
			for(int i = 0; i < SIZEOF_u48; i++)
				cpu->memory[cpu->r.r_sp + i] = cpu->memory[cpu->r.r_pc + i];
			cpu->r.r_pc += 1 + SIZEOF_u48;
			break;
		case OPC_push_double:
			cpu->r.r_sp -= SIZEOF_double;
			for(int i = 0; i < SIZEOF_double; i++)
				cpu->memory[cpu->r.r_sp + i] = cpu->memory[cpu->r.r_pc + i];
			cpu->r.r_pc += 1 + SIZEOF_double;
			break;
		
		default:
			return 1;
	}
	return 0;
}