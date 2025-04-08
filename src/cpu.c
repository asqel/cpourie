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

void set_register(cpu_t *cpu, u8 reg, u32 value) {
	switch (reg & 0b1111) {
		case 0b0000:
			cpu->r.r_do = value;
			break;
		case 0b0001:
			cpu->r.r_do$ = value;
			break;
		case 0b0010:
			cpu->r.r_re = value;
			break;
		case 0b0011:
			cpu->r.r_re$ = value;
			break;
		case 0b0100:
			cpu->r.r_mi = value;
			break;
		case 0b0101:
			cpu->r.r_fa = value;
			break;
		case 0b0110:
			cpu->r.r_fa$ = value;
			break;
		case 0b0111:
			cpu->r.r_so = value;
			break;
		case 0b1000:
			cpu->r.r_so$ = value;
			break;
		case 0b1001:
			cpu->r.r_la = value;
			break;
		case 0b1010:
			cpu->r.r_la$ = value;
			break;
		case 0b1011:
			cpu->r.r_si = value;
			break;
		case 0b1100:
			cpu->r.r_in = value;
			break;
		case 0b1101:
			cpu->r.r_ou = value;
			break;
		case 0b1110:
			cpu->r.r_sp = value;
			break;
		case 0b1111:
			cpu->r.r_bp = value;
			break;
	}
}

u32 get_register(cpu_t *cpu, u8 reg) {
	switch (reg & 0b1111) {
		case 0b0000:
			return cpu->r.r_do;
		case 0b0001:
			return cpu->r.r_do$;
		case 0b0010:
			return cpu->r.r_re;
		case 0b0011:
			return cpu->r.r_re$;
		case 0b0100:
			return cpu->r.r_mi;
		case 0b0101:
			return cpu->r.r_fa;
		case 0b0110:
			return cpu->r.r_fa$;
		case 0b0111:
			return cpu->r.r_so;
		case 0b1000:
			return cpu->r.r_so$;
		case 0b1001:
			return cpu->r.r_la;
		case 0b1010:
			return cpu->r.r_la$;
		case 0b1011:
			return cpu->r.r_si;
		case 0b1100:
			return cpu->r.r_in;
		case 0b1101:
			return cpu->r.r_ou;
		case 0b1110:
			return cpu->r.r_sp;
		case 0b1111:
			return cpu->r.r_bp;
	}
}

i32 get_register_signed(cpu_t *cpu, u8 reg) {
	u32 val = get_register(cpu, reg);
	return *((i32 *)&val);
}

void set_register_signed(cpu_t *cpu, u8 reg, i32 value) {
	u32 val = *((u32 *)&value);
	set_register(cpu, reg, val);
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

    // reset the color
    printf("\033[0m");

    va_end(args);
}

static void print_u32(u32 x) {
	char *digits = "0123456789ABCDEF";
	u8 *num = (u8 *)(&x);
	u32 col1 = x & 0xFFFFFF;
	u32 col2 = (x & 0xFFFFFF000000) >> 24;
	for (int i = 5; i >= 0; i--) {
		if (i == 5 || i == 4 || i == 3)
			printf_rgb(col2, "%c%c", digits[(num[i] >> 4) & 0xf], digits[num[i] & 0xf]);
		else
			printf_rgb(col1, "%c%c", digits[(num[i] >> 4) & 0xf], digits[num[i] & 0xf]);
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