#include "cpu.h"

void alu_add_unsigned(cpu_t *cpu, u8 regA, u8 regB, u8 regOUT) {
	u32 valA = get_register(cpu, regA);
	u32 valB = get_register(cpu, regB);
	u32 valOUT = valA + valB;

	set_register(cpu, regOUT, valOUT);
}


void alu_add_signed(cpu_t *cpu, u8 regA, u8 regB, u8 regOUT) {
	i32 valA = get_register_signed(cpu, regA);
	i32 valB = get_register_signed(cpu, regB);
	i32 valOUT = valA + valB;

	set_register_signed(cpu, regOUT, valOUT);
}

