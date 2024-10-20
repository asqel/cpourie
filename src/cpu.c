#include "cpu.h"
#include <stdlib.h>
#include <string.h>

cpu_t *new_cpu() {
	cpu_t *cpu = malloc(sizeof(cpu_t));

	memset(cpu->memory,      0, sizeof(u8) * MEM_SIZE);

	memset(cpu->r.r_red,     0, sizeof(double) * 6);
	memset(cpu->r.r_green,   0, sizeof(double) * 6);
	memset(cpu->r.r_blue,    0, sizeof(double) * 6);
	memset(cpu->r.r_magenta, 0, sizeof(double) * 6);
	memset(cpu->r.r_yellow,  0, sizeof(double) * 6);
	memset(cpu->r.r_cyan,    0, sizeof(double) * 6);
	memset(cpu->r.r_white,   0, sizeof(double) * 6);
	memset(cpu->r.r_black,   0, sizeof(double) * 6);

	memset(cpu->r.r_do, 0, sizeof(u48) * 7);
	memset(cpu->r.r_re, 0, sizeof(u48) * 7);
	memset(cpu->r.r_mi, 0, sizeof(u48) * 7);
	memset(cpu->r.r_fa, 0, sizeof(u48) * 7);
	memset(cpu->r.r_so, 0, sizeof(u48) * 7);
	memset(cpu->r.r_la, 0, sizeof(u48) * 7);
	memset(cpu->r.r_si, 0, sizeof(u48) * 7);

	cpu->r.r_bp = MEM_SIZE - 1;
	cpu->r.r_sp = cpu->r.r_bp;
	cpu->r.r_pc = 0;
	cpu->r.r_status = 0;

	return cpu;
}

void free_cpu(cpu_t *cpu) {
	free(cpu);
}

static void print_u48(u48 x) {
	char *digits = "0123456789ABCDEF";
	u8 *num = (u8 *)(&x);
	for (int i = 5; i >= 0; i--) {
		printf("%c%c", digits[(num[i] >> 4) & 0xf], digits[num[i] & 0xf]);
	}
}

static void print_register_vec_u48_from(u48 *reg, char *name, int idx) {
	int len = strlen(name);
	if (idx == 0)
		printf("%s", name);
	else
		for (int i = 0; i < len; i++)
			printf(" ");
	printf("  ");
	print_u48(reg[0 + idx]);
	if (idx < 6) {
		printf("  ");
		print_u48(reg[1 + idx]);
	}
	else
		printf("              ");
	if (idx < 5) {
		printf("  ");
		print_u48(reg[2 + idx]);
	}
	else
		printf("              ");
}

void dump_registers(cpu_t *cpu) {
	printf("pc  ");
	print_u48(cpu->r.r_pc);
	printf("  ");
	printf("status  ");
	print_u48(cpu->r.r_status);
	printf("\n");

	printf("bp  ");
	print_u48(cpu->r.r_bp);
	printf("  ");
	printf("    sp  ");
	print_u48(cpu->r.r_sp);
	printf("\n\n");

	print_register_vec_u48_from(cpu->r.r_do, "do", 0);
	printf("  ");
	print_register_vec_u48_from(cpu->r.r_re, "re", 0);
	printf("\n");
	print_register_vec_u48_from(cpu->r.r_do, "do", 3);
	printf("  ");
	print_register_vec_u48_from(cpu->r.r_re, "re", 3);
	printf("\n");
	print_register_vec_u48_from(cpu->r.r_do, "do", 6);
	printf("  ");
	print_register_vec_u48_from(cpu->r.r_re, "re", 6);
	printf("\n\n");

	print_register_vec_u48_from(cpu->r.r_mi, "mi", 0);
	printf("  ");
	print_register_vec_u48_from(cpu->r.r_fa, "fa", 0);
	printf("\n");
	print_register_vec_u48_from(cpu->r.r_mi, "mi", 3);
	printf("  ");
	print_register_vec_u48_from(cpu->r.r_fa, "fa", 3);
	printf("\n");
	print_register_vec_u48_from(cpu->r.r_mi, "mi", 6);
	printf("  ");
	print_register_vec_u48_from(cpu->r.r_fa, "fa", 6);
	printf("\n\n");

	
	print_register_vec_u48_from(cpu->r.r_so, "so", 0);
	printf("  ");
	print_register_vec_u48_from(cpu->r.r_la, "la", 0);
	printf("\n");
	print_register_vec_u48_from(cpu->r.r_so, "so", 3);
	printf("  ");
	print_register_vec_u48_from(cpu->r.r_la, "la", 3);
	printf("\n");
	print_register_vec_u48_from(cpu->r.r_so, "so", 6);
	printf("  ");
	print_register_vec_u48_from(cpu->r.r_la, "la", 6);
	printf("\n\n");

	print_register_vec_u48_from(cpu->r.r_so, "si", 0);
	printf("\n");
	print_register_vec_u48_from(cpu->r.r_so, "si", 3);
	printf("\n");
	print_register_vec_u48_from(cpu->r.r_so, "si", 6);
	printf("\n\n");
}