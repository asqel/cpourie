#include "cpu.h"

void handler_c0_cmp(cpu_t *cpu) {
	if (!can_acces_u8(cpu, cpu->r.r_pc + 1))
		return set_interrupt(cpu, CPU_INT_BADOPCODE);

	u8 info = get_u8(cpu, cpu->r.r_pc + 1);
	update_status_comp(cpu, *get_Uregister_ptr(cpu, info >> 4), *get_Uregister_ptr(cpu, info & 0b1111));
	cpu->r.r_pc += 2;
}

void handler_c1_cmp(cpu_t *cpu) {
	if (!can_acces_u8(cpu, cpu->r.r_pc + 1))
		return set_interrupt(cpu, CPU_INT_BADOPCODE);
	u8 info = get_u8(cpu, cpu->r.r_pc + 1);
	u8 mod = info & 0b11;
	u8 regA = info >> 4;
	u8 TT = (info >> 2) & 0b11;
	if (mod == 0b01 || mod == 0b10 || TT == 0b11)
		return set_interrupt(cpu, CPU_INT_BADOPCODE);
	if (!can_acces_u_with_size(cpu, cpu->r.r_pc + 2, TT))
		return set_interrupt(cpu, CPU_INT_BADOPCODE);
	u32 val = get_u_with_size(cpu, cpu->r.r_pc + 2, TT);
	u32 *reg_ptr = get_Uregister_ptr(cpu, regA);
	if (mod == 0)
		update_status_comp(cpu, (*reg_ptr) & TYPE_MASK(TT), val);
	else {
		if (!can_acces_u_with_size(cpu, *reg_ptr, TT))
			return set_interrupt(cpu, CPU_INT_OUT_BOUND);
		update_status_comp(cpu, get_u_with_size(cpu, *reg_ptr, TT), val);
	}
	cpu->r.r_pc += 2 + TYPE_SIZE(TT);
}

void handler_c2_cmp(cpu_t *cpu) {
	if (!can_acces_u8(cpu, cpu->r.r_pc + 1))
		return set_interrupt(cpu, CPU_INT_BADOPCODE);
	u8 info = get_u8(cpu, cpu->r.r_pc + 1);

	u8 valA = *get_Uregister_ptr(cpu, info >> 4);
	u32 addrB = *get_Uregister_ptr(cpu, info & 0b1111);
	if (!can_acces_u8(cpu, addrB))
		return set_interrupt(cpu, CPU_INT_OUT_BOUND);
	u8 valB = get_u8(cpu, addrB);
	update_status_comp(cpu, valA, valB);
	cpu->r.r_pc += 2;
}

void handler_c3_cmp(cpu_t *cpu) {
	if (!can_acces_u8(cpu, cpu->r.r_pc + 1))
		return set_interrupt(cpu, CPU_INT_BADOPCODE);
	u8 info = get_u8(cpu, cpu->r.r_pc + 1);

	u16 valA = *get_Uregister_ptr(cpu, info >> 4);
	u32 addrB = *get_Uregister_ptr(cpu, info & 0b1111);
	if (!can_acces_u16(cpu, addrB))
		return set_interrupt(cpu, CPU_INT_OUT_BOUND);
	u16 valB = get_u16(cpu, addrB);
	update_status_comp(cpu, valA, valB);
	cpu->r.r_pc += 2;
}

void handler_c4_cmp(cpu_t *cpu) {
	if (!can_acces_u8(cpu, cpu->r.r_pc + 1))
		return set_interrupt(cpu, CPU_INT_BADOPCODE);
	u8 info = get_u8(cpu, cpu->r.r_pc + 1);

	u32 valA = *get_Uregister_ptr(cpu, info >> 4);
	u32 addrB = *get_Uregister_ptr(cpu, info & 0b1111);
	if (!can_acces_u32(cpu, addrB))
		return set_interrupt(cpu, CPU_INT_OUT_BOUND);
	u32 valB = get_u32(cpu, addrB);
	update_status_comp(cpu, valA, valB);
	cpu->r.r_pc += 2;
}

void handler_c5_cmp(cpu_t *cpu) {
	if (!can_acces_u8(cpu, cpu->r.r_pc + 1))
		return set_interrupt(cpu, CPU_INT_BADOPCODE);
	u8 info = get_u8(cpu, cpu->r.r_pc + 1);

	u32 addrA = *get_Uregister_ptr(cpu, info >> 4);
	u32 addrB = *get_Uregister_ptr(cpu, info & 0b1111);
	if (!can_acces_u8(cpu, addrA) || !can_acces_u8(cpu, addrB))
		return set_interrupt(cpu, CPU_INT_OUT_BOUND);
	update_status_comp(cpu, get_u8(cpu, addrA), get_u8(cpu, addrB));
	cpu->r.r_pc += 2;
}

void handler_c6_cmp(cpu_t *cpu) {
	if (!can_acces_u8(cpu, cpu->r.r_pc + 1))
		return set_interrupt(cpu, CPU_INT_BADOPCODE);
	u8 info = get_u8(cpu, cpu->r.r_pc + 1);

	u32 addrA = *get_Uregister_ptr(cpu, info >> 4);
	u32 addrB = *get_Uregister_ptr(cpu, info & 0b1111);
	if (!can_acces_u16(cpu, addrA) || !can_acces_u16(cpu, addrB))
		return set_interrupt(cpu, CPU_INT_OUT_BOUND);
	update_status_comp(cpu, get_u16(cpu, addrA), get_u16(cpu, addrB));
	cpu->r.r_pc += 2;
}

void handler_c7_cmp(cpu_t *cpu) {
	if (!can_acces_u8(cpu, cpu->r.r_pc + 1))
		return set_interrupt(cpu, CPU_INT_BADOPCODE);
	u8 info = get_u8(cpu, cpu->r.r_pc + 1);

	u32 addrA = *get_Uregister_ptr(cpu, info >> 4);
	u32 addrB = *get_Uregister_ptr(cpu, info & 0b1111);
	if (!can_acces_u32(cpu, addrA) || !can_acces_u32(cpu, addrB))
		return set_interrupt(cpu, CPU_INT_OUT_BOUND);
	update_status_comp(cpu, get_u32(cpu, addrA), get_u32(cpu, addrB));
	cpu->r.r_pc += 2;
}