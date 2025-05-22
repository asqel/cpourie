#include "cpu.h"

void handler_d0_swap(cpu_t *cpu) {
	if (!can_acces_u8(cpu, cpu->r.r_pc + 1))
		return set_interrupt(cpu, CPU_INT_BADOPCODE);
	u8 info = get_u8(cpu, cpu->r.r_pc + 1);

	u32 *regA = get_Uregister_ptr(cpu, info >> 4);
	u32 *regB = get_Uregister_ptr(cpu, info & 0b1111);
	u32 tmp = 0;

	tmp = *regA;
	*regB = *regA;
	*regA = tmp;
	cpu->r.r_pc += 2;
}

void handler_f0_setsdt(cpu_t *cpu) {
	if (cpu->r.level != CPU_LV_K)
		return set_interrupt(cpu, CPU_INT_PRIVILEGE);
	if (!can_acces_u8(cpu, cpu->r.r_pc + 1))
		return set_interrupt(cpu, CPU_INT_BADOPCODE);
	u8 info = get_u8(cpu, cpu->r.r_pc + 1);

	u32 *regA = get_Uregister_ptr(cpu, info >> 4);
	u32 *regB = get_Uregister_ptr(cpu, info & 0b1111);
	cpu->r.sdt[(*regA) & 0xFF] = *regB;
	cpu->r.r_pc += 2;
}

void handler_f1_setddt(cpu_t *cpu) {
	if (cpu->r.level != CPU_LV_K)
		return set_interrupt(cpu, CPU_INT_PRIVILEGE);
	if (!can_acces_u8(cpu, cpu->r.r_pc + 1))
		return set_interrupt(cpu, CPU_INT_BADOPCODE);
	u8 info = get_u8(cpu, cpu->r.r_pc + 1);

	u32 *regA = get_Uregister_ptr(cpu, info >> 4);
	u32 *regB = get_Uregister_ptr(cpu, info & 0b1111);
	cpu->r.ddt[(*regA) & 0xFF] = *regB;
	cpu->r.r_pc += 2;
}

void handler_f2_syscall(cpu_t *cpu) {
	if (!can_acces_u8(cpu, cpu->r.r_pc + 1))
		return set_interrupt(cpu, CPU_INT_BADOPCODE);
	u8 info = get_u8(cpu, cpu->r.r_pc + 1);
	u32 addr = cpu->r.sdt[info];
	if (addr == 0)
		return set_interrupt(cpu, CPU_INT_OUT_BOUND);
	if (cpu_push_u32(cpu, cpu->r.r_pc + 2) == -1)
		return set_interrupt(cpu, CPU_INT_OUT_BOUND);
	if (cpu_push_level(cpu) == -1)
		return set_interrupt(cpu, CPU_INT_OUT_BOUND);
	cpu->r.r_pc = addr;
	cpu->r.level = CPU_LV_K;
}

void handler_f3_drivcall(cpu_t *cpu) {
	if (!can_acces_u8(cpu, cpu->r.r_pc + 1))
		return set_interrupt(cpu, CPU_INT_BADOPCODE);
	u8 info = get_u8(cpu, cpu->r.r_pc + 1);
	u32 addr = cpu->r.ddt[info];
	if (addr == 0)
		return set_interrupt(cpu, CPU_INT_OUT_BOUND);
	if (cpu_push_u32(cpu, cpu->r.r_pc + 2) == -1)
		return set_interrupt(cpu, CPU_INT_OUT_BOUND);
	if (cpu_push_level(cpu) == -1)
		return set_interrupt(cpu, CPU_INT_OUT_BOUND);
	cpu->r.r_pc = addr;
	cpu->r.level = CPU_LV_D;
}

void handler_f6_set_umem(cpu_t *cpu) {
	if (cpu->r.level != CPU_LV_K)
		return set_interrupt(cpu, CPU_INT_PRIVILEGE);
	cpu->r.umem = cpu->r.r_si;
}

void handler_f7_set_umem(cpu_t *cpu) {
	if (cpu->r.level != CPU_LV_K)
		return set_interrupt(cpu, CPU_INT_PRIVILEGE);
	cpu->r.dmem = cpu->r.r_si;
}

void handler_f8_set_lvl_sp(cpu_t *cpu) {
	if (cpu->r.level != CPU_LV_K)
		return set_interrupt(cpu, CPU_INT_PRIVILEGE);
	cpu->r.level_sp = cpu->r.r_si;
}

void handler_f9_set_lvl_bp(cpu_t *cpu) {
	if (cpu->r.level != CPU_LV_K)
		return set_interrupt(cpu, CPU_INT_PRIVILEGE);
	cpu->r.level_bp = cpu->r.r_si;
}

void handler_fa_set_lvl_stack_len(cpu_t *cpu) {
	if (cpu->r.level != CPU_LV_K)
		return set_interrupt(cpu, CPU_INT_PRIVILEGE);
	cpu->r.level_stack_len = cpu->r.r_si;
}

void handler_fb_read_lvl_sp(cpu_t *cpu) {
	if (cpu->r.level != CPU_LV_K)
		return set_interrupt(cpu, CPU_INT_PRIVILEGE);
	cpu->r.r_si = cpu->r.level_sp;
}

void handler_fb_read_lvl_bp(cpu_t *cpu) {
	if (cpu->r.level != CPU_LV_K)
		return set_interrupt(cpu, CPU_INT_PRIVILEGE);
	cpu->r.r_si = cpu->r.level_bp;
}

void handler_fb_read_lvl_stack_len(cpu_t *cpu) {
	if (cpu->r.level != CPU_LV_K)
		return set_interrupt(cpu, CPU_INT_PRIVILEGE);
	cpu->r.r_si = cpu->r.level_stack_len;
}

void handler_00_halt(cpu_t *cpu) {
	if (cpu->r.level != CPU_LV_K)
		return set_interrupt(cpu, CPU_INT_PRIVILEGE);
	cpu->is_halted = 1;
}

void handler_01_halt_int(cpu_t *cpu) {
	cpu->is_halted = 2;
}