#include "cpu.h"

void update_status_comp(cpu_t *cpu, u32 a, u32 b) {
	if (a < b)
		cpu->r.r_status |= (1 << 1);
	else
		cpu->r.r_status &= ~(1 << 1);

	if (a > b)
		cpu->r.r_status |= (1 << 2);
	else
		cpu->r.r_status &= ~(1 << 2);

	if (a == b)
		cpu->r.r_status |= (1 << 3);
	else
		cpu->r.r_status &= ~(1 << 3);

	i32 Ia = *(i32 *)&a;
	i32 Ib = *(i32 *)&b;
	if (Ia < Ib)
		cpu->r.r_status |= (1 << 4);
	else
		cpu->r.r_status &= ~(1 << 4);

	if (Ia > Ib)
		cpu->r.r_status |= (1 << 5);
	else
		cpu->r.r_status &= ~(1 << 5);
}

void update_status_mod(cpu_t *cpu, u32 a, u32 b) {
	if (a % b != 0)
		cpu->r.r_status |= 1;
	else
		cpu->r.r_status &= ~1;
}