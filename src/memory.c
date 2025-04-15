#include "cpu.h"

int can_acces_u8(cpu_t *cpu, u32 addr) {
	if (addr >= cpu->mem_size)
		return 0;
	if (cpu->r.level == CPU_LV_K)
		return addr < cpu->mem_size;
	if (cpu->r.level == CPU_LV_D || cpu->r.level == CPU_LV_U) {
		u32 umem = cpu->r.umem;
		while (umem + 8 < cpu->mem_size) {
			u32 start = *(u32 *)&cpu->memory[start];
			u32 end = *(u32 *)&cpu->memory[start + 4];
			if (start >= end)
				break;
			if (start <= addr && addr < end)
				return (1);
			umem += 8;
		}
	}
	if (cpu->r.level == CPU_LV_D) {
		u32 dmem = cpu->r.dmem;
		while (dmem + 8 < cpu->mem_size) {
			u32 start = *(u32 *)&cpu->memory[start];
			u32 end = *(u32 *)&cpu->memory[start + 4];
			if (start >= end)
				break;
			if (start <= addr && addr < end)
				return (1);
			dmem += 8;
		}
		if (PCI_BASE <= addr && addr < PCI_MAX_ADDR)
			return (1);
	}
	return (0);
}

int can_acces_u16(cpu_t *cpu, u32 addr) {
	if (addr >= cpu->mem_size)
		return 0;
	if (cpu->r.level == CPU_LV_K)
		return addr + 1 < cpu->mem_size;
	if (cpu->r.level == CPU_LV_D || cpu->r.level == CPU_LV_U) {
		u32 umem = cpu->r.umem;
		while (umem + 8 < cpu->mem_size) {
			u32 start = *(u32 *)&cpu->memory[start];
			u32 end = *(u32 *)&cpu->memory[start + 4];
			if (start >= end)
				break;
			if (start <= addr && addr + 1 < end)
				return (1);
			umem += 8;
		}
	}
	if (cpu->r.level == CPU_LV_D) {
		u32 dmem = cpu->r.dmem;
		while (dmem + 8 < cpu->mem_size) {
			u32 start = *(u32 *)&cpu->memory[start];
			u32 end = *(u32 *)&cpu->memory[start + 4];
			if (start >= end)
				break;
			if (start <= addr && addr + 1 < end)
				return (1);
			dmem += 8;
		}
		if (PCI_BASE <= addr && addr + 1 < PCI_MAX_ADDR)
			return (1);
	}
	return (0);
}

int can_acces_u32(cpu_t *cpu, u32 addr) {
	if (addr >= cpu->mem_size)
		return 0;
	if (cpu->r.level == CPU_LV_K)
		return addr + 3 < cpu->mem_size;
	if (cpu->r.level == CPU_LV_D || cpu->r.level == CPU_LV_U) {
		u32 umem = cpu->r.umem;
		while (umem + 8 < cpu->mem_size) {
			u32 start = *(u32 *)&cpu->memory[start];
			u32 end = *(u32 *)&cpu->memory[start + 4];
			if (start >= end)
				break;
			if (start <= addr && addr + 3 < end)
				return (1);
			umem += 8;
		}
	}
	if (cpu->r.level == CPU_LV_D) {
		u32 dmem = cpu->r.dmem;
		while (dmem + 8 < cpu->mem_size) {
			u32 start = *(u32 *)&cpu->memory[start];
			u32 end = *(u32 *)&cpu->memory[start + 4];
			if (start >= end)
				break;
			if (start <= addr && addr + 3 < end)
				return (1);
			dmem += 8;
		}
		if (PCI_BASE <= addr && addr + 3 < PCI_MAX_ADDR)
			return (1);
	}
	return (0);
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

