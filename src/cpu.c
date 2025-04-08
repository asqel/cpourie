#include "cpu.h"
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include "memory.h"

cpu_t *new_cpu(u32 mem_size) {
	cpu_t *cpu = calloc(1, sizeof(cpu_t));

	cpu->mem_size = mem_size;
	cpu->memory = malloc(sizeof(u8) * cpu->mem_size);\

	return cpu;
}

void free_cpu(cpu_t *cpu) {
	free(cpu->memory);
	free(cpu);
}

static void print_u32(u32 x) {
	char *digits = "0123456789ABCDEF";
	u8 *num = (u8 *)(&x);
	u32 col1 = x & 0xFFFFFF;
	u32 col2 = (x & 0xFFFFFF000000) >> 24;
	for (int i = 5; i >= 0; i--) {
		printf("%c%c", digits[(num[i] >> 4) & 0xf], digits[num[i] & 0xf]);
	}
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