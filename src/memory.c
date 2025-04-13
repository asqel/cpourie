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

i32 get_i_with_size(cpu_t *cpu, u32 addr, u8 size) {
	switch (size) {
		case 0b00:
			return cpu->memory[addr];
		case 0b01:
			return *(u16 *)&cpu->memory[addr];
		case 0b10:
			return *(u32 *)&cpu->memory[addr];
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

void set_u_with_size(cpu_t *cpu, u32 addr, u8 size, u32 val) {
	switch (size) {
		case 0b00:
			return set_u8(cpu, addr, val);
		case 0b01:
			return set_u16(cpu, addr, val);
		case 0b10:
			return set_u32(cpu, addr, val);
		default:
			break;
	}
	fprintf(stderr, "Invalid size in get_u_with_size\n");
	exit(1);
}

void set_u32(cpu_t *cpu, u32 addr, u32 val) {
	*((u32 *)&cpu->memory[addr]) = val;
}

void set_u16(cpu_t *cpu, u32 addr, u16 val) {
	*((u16 *)&cpu->memory[addr]) = val;
}

void set_u8(cpu_t *cpu, u32 addr, u8 val) {
	*((u8 *)&cpu->memory[addr]) = val;
}

