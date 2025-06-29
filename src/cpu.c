#include "cpu.h"
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include "memory.h"

cpu_t *new_cpu(u32 mem_size) {
	cpu_t *cpu = calloc(1, sizeof(cpu_t));

	cpu->mem_size = mem_size;
	cpu->memory = malloc(sizeof(u8) * cpu->mem_size);
	cpu->r.r_pc = CPU_START_ADDR;

	return cpu;
}

void free_cpu(cpu_t *cpu) {
	free(cpu->memory);
	free(cpu);
}

static void print_u32(u32 x) {
	char *digits = "0123456789ABCDEF";
	printf("%c%c", digits[((x >> 24) >> 4) & 0xf], digits[(x >> 24) & 0xf]);
	printf("%c%c", digits[((x >> 16) >> 4) & 0xf], digits[(x >> 16) & 0xf]);
	printf("%c%c", digits[((x >> 8) >> 4) & 0xf], digits[(x >> 8) & 0xf]);
	printf("%c%c", digits[((x >> 0) >> 4) & 0xf], digits[(x >> 0) & 0xf]);
}

static void print_register_u32_from(u32 reg, char *name) {
	int len = strlen(name);
	printf("%s", name);
	for (int i = 0; i < 4 - len; i++)
		printf(" ");

	print_u32(reg);
}

void dump_registers(cpu_t *cpu) {
	printf("pc  ");
	print_u32(cpu->r.r_pc);
	printf("  ");
	printf("status  ");
	print_u32(cpu->r.r_status);
	printf("\n");

	print_register_u32_from(cpu->r.r_do, "do");
	printf("  ");
	print_register_u32_from(cpu->r.r_do$, "do$");
	printf("  ");
	print_register_u32_from(cpu->r.r_re, "re");
	printf("  ");
	print_register_u32_from(cpu->r.r_re$, "re$");
	printf("\n\n");

	print_register_u32_from(cpu->r.r_mi, "mi");
	printf("  ");
	print_register_u32_from(cpu->r.r_fa, "fa");
	printf("  ");
	print_register_u32_from(cpu->r.r_fa$, "fa$");
	printf("  ");
	print_register_u32_from(cpu->r.r_so, "so");
	printf("\n\n");

	print_register_u32_from(cpu->r.r_so$, "so$");
	printf("  ");
	print_register_u32_from(cpu->r.r_la, "la");
	printf("  ");
	print_register_u32_from(cpu->r.r_la$, "la$");
	printf("  ");
	print_register_u32_from(cpu->r.r_si, "si");
	printf("\n\n");

	print_register_u32_from(cpu->r.r_in, "in");
	printf("  ");
	print_register_u32_from(cpu->r.r_ou, "ou");
	printf("  ");
	print_register_u32_from(cpu->r.r_sp, "sp");
	printf("  ");
	print_register_u32_from(cpu->r.r_bp, "bp");
	printf("\n\n");
}

void set_interrupt(cpu_t *cpu, u8 interrupt) {
	cpu->r.interrupt = interrupt;
}

u32 *get_Uregister_ptr(cpu_t *cpu, u8 reg) {
	switch (reg) {
		case 0:  return &cpu->r.r_do;
		case 1:  return &cpu->r.r_do$;
		case 2:  return &cpu->r.r_re;
		case 3:  return &cpu->r.r_re$;
		case 4:  return &cpu->r.r_mi;
		case 5:  return &cpu->r.r_fa;
		case 6:  return &cpu->r.r_fa$;
		case 7:  return &cpu->r.r_so;
		case 8:  return &cpu->r.r_so$;
		case 9: return &cpu->r.r_la;
		case 10: return &cpu->r.r_la$;
		case 11: return &cpu->r.r_si;
		case 12: return &cpu->r.r_in;
		case 13: return &cpu->r.r_ou;
		case 14: return &cpu->r.r_sp;
		case 15: return &cpu->r.r_bp;
		default: return NULL;
	}
}

i32 *get_Iregister_ptr(cpu_t *cpu, u8 reg) {
	return (i32 *)get_Uregister_ptr(cpu, reg);
}
