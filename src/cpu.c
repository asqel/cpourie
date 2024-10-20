#include "cpu.h"
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

cpu_t *new_cpu(u48 mem_size) {
	cpu_t *cpu = malloc(sizeof(cpu_t));

	cpu->mem_size = mem_size;
	cpu->memory = malloc(sizeof(u8) * cpu->mem_size);

	memset(cpu->memory,      0, sizeof(u8) * cpu->mem_size);

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

	cpu->r.r_bp = cpu->mem_size - 1;
	cpu->r.r_sp = cpu->r.r_bp;
	cpu->r.r_pc = 0;
	cpu->r.r_status = 0;

	return cpu;
}

void free_cpu(cpu_t *cpu) {
	free(cpu->memory);
	free(cpu);
}

void printf_rgb(uint32_t rgb, const char *fmt, ...)
{
    va_list args;
    va_start(args, fmt);

    // Set the background color
    printf("\033[48;2;%d;%d;%dm", (rgb >> 16) & 0xFF, (rgb >> 8) & 0xFF, rgb & 0xFF);

    // reverse the color
    uint32_t r = 0xFF - ((rgb >> 16) & 0xFF);
    uint32_t g = 0xFF - ((rgb >> 8) & 0xFF);
    uint32_t b = 0xFF - (rgb & 0xFF);

    // Set the text color
    printf("\033[38;2;%d;%d;%dm", r, g, b);

    vprintf(fmt, args);

    // Reset the color
    printf("\033[0m");

    va_end(args);
}

static void print_u48(u48 x) {
	char *digits = "0123456789ABCDEF";
	u8 *num = (u8 *)(&x);
	u32 col1 = x & 0xFFFFFF;
	u32 col2 = (x >> 32) & 0xFFFFFF;
	for (int i = 5; i >= 0; i--) {
		if (i == 5 || i == 4 || i == 3)
			printf_rgb(col2, "%c%c", digits[(num[i] >> 4) & 0xf], digits[num[i] & 0xf]);
		else
			printf_rgb(col1, "%c%c", digits[(num[i] >> 4) & 0xf], digits[num[i] & 0xf]);
	}
}

static void print_register_vec_u48_from(u48 *reg, char *name, int idx) {
	if (idx != 0 && idx != 2)
		return ;
	int len = strlen(name);
	if (idx == 0)
		printf("%s", name);
	else
		for (int i = 0; i < len; i++)
			printf(" ");
	printf("  ");
	print_u48(reg[0 + idx]);
	printf("  ");
	print_u48(reg[1 + idx]);
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
	print_register_vec_u48_from(cpu->r.r_do, "do", 2);
	printf("  ");
	print_register_vec_u48_from(cpu->r.r_re, "re", 2);
	printf("\n\n");

	print_register_vec_u48_from(cpu->r.r_mi, "mi", 0);
	printf("  ");
	print_register_vec_u48_from(cpu->r.r_fa, "fa", 0);
	printf("\n");
	print_register_vec_u48_from(cpu->r.r_mi, "mi", 2);
	printf("  ");
	print_register_vec_u48_from(cpu->r.r_fa, "fa", 2);
	printf("\n\n");

	
	print_register_vec_u48_from(cpu->r.r_so, "so", 0);
	printf("  ");
	print_register_vec_u48_from(cpu->r.r_la, "la", 0);
	printf("\n");
	print_register_vec_u48_from(cpu->r.r_so, "so", 2);
	printf("  ");
	print_register_vec_u48_from(cpu->r.r_la, "la", 2);
	printf("\n\n");

	print_register_vec_u48_from(cpu->r.r_so, "si", 0);
	printf("\n");
	print_register_vec_u48_from(cpu->r.r_so, "si", 2);
	printf("\n\n");
}