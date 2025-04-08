#include "cpu.h"

int can_acces_u8(cpu_t *cpu, u32 addr) {
	return addr < cpu->mem_size;
}

int can_acces_u16(cpu_t *cpu, u32 addr) {
	return addr + 1 < cpu->mem_size && addr < cpu->mem_size;
}

int can_acces_u32(cpu_t *cpu, u32 addr) {
	return addr + 3 < cpu->mem_size && addr < cpu->mem_size;
}

u32 get_u8(cpu_t *cpu, u32 addr) {
	return cpu->memory[addr];
}

u32 get_u16(cpu_t *cpu, u32 addr) {
	return cpu->memory[addr] | ((u32)cpu->memory[addr + 1] << 8);
}

u32 get_u32(cpu_t *cpu, u32 addr) {
	return cpu->memory[addr] | ((u32)cpu->memory[addr + 1] << 8) | ((u32)cpu->memory[addr + 2] << 16) | ((u32)cpu->memory[addr + 3] << 24);
}

u32 get_u_with_size(cpu_t *cpu, u32 addr, u8 size) {
	switch (size) {
		case 0b00:
			return get_u8(cpu, addr);
		case 0b01:
			return get_u16(cpu, addr);
		case 0b10:
			return get_u32(cpu, addr);
		default:
			break;
	}
	fprintf(stderr, "Invalid size in get_u_with_size\n");
	exit(1);
}

int can_acces_u_with_size(cpu_t *cpu, u32 addr, u8 size) {
	switch (size) {
		case 0b00:
			return can_acces_u8(cpu, addr);
		case 0b01:
			return can_acces_u16(cpu, addr);
		case 0b10:
			return can_acces_u32(cpu, addr);
		default:
			break;
	}
	fprintf(stderr, "Invalid size in can_acces_u_with_size\n");
	exit(1);
}