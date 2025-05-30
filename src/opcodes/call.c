#include "cpu.h"


void handler_90_call(cpu_t *cpu) {
	if (!can_acces_u8(cpu, cpu->r.r_pc + 1))
		return set_interrupt(cpu, CPU_INT_BADOPCODE);
	u8 info = get_u8(cpu, cpu->r.r_pc + 1);

	u8 reg = info & 0b1111;
	u8 cond = info >> 4;
	int ret = cpu_do_call(cpu, *get_Uregister_ptr(cpu, reg), cond, cpu->r.r_pc + 2);
	if (ret == 2)
		return set_interrupt(cpu, CPU_INT_BADOPCODE);
	if (ret == -1)
		return set_interrupt(cpu, CPU_INT_OUT_BOUND);
	if (ret == 1)
		return ;
	cpu->r.r_pc += 2;
}

void handler_91_call(cpu_t *cpu) {
	if (!can_acces_u8(cpu, cpu->r.r_pc + 1) || !can_acces_u32(cpu, cpu->r.r_pc + 2))
		return set_interrupt(cpu, CPU_INT_BADOPCODE);
	u8 info = get_u8(cpu, cpu->r.r_pc + 1);
	u32 addr = get_u32(cpu, cpu->r.r_pc + 2);
	if ((info & 0b1111) != 0)
		return set_interrupt(cpu, CPU_INT_BADOPCODE);
	int ret = cpu_do_call(cpu, addr, info >> 4, cpu->r.r_pc + 2 + sizeof(u32));
	if (ret == 2)
		return set_interrupt(cpu, CPU_INT_BADOPCODE);
	if (ret == -1)
		return set_interrupt(cpu, CPU_INT_OUT_BOUND);
	if (ret == 1)
		return ;
	cpu->r.r_pc += 2 + sizeof(u32);
}

void handler_92_call(cpu_t *cpu) {
	if (!can_acces_u8(cpu, cpu->r.r_pc + 1))
		return set_interrupt(cpu, CPU_INT_BADOPCODE);
	u8 info = get_u8(cpu, cpu->r.r_pc + 1);

	u8 reg = info & 0b1111;
	u8 cond = info >> 4;

	u32 *reg_ptr = get_Uregister_ptr(cpu, reg);
	if (!can_acces_u32(cpu, *reg_ptr))
		return set_interrupt(cpu, CPU_INT_OUT_BOUND);
	u32 addr = get_u32(cpu, *reg_ptr);

	int ret = cpu_do_call(cpu, addr, cond, cpu->r.r_pc + 2);
	if (ret == 2)
		return set_interrupt(cpu, CPU_INT_BADOPCODE);
	if (ret == -1)
		return set_interrupt(cpu, CPU_INT_OUT_BOUND);
	if (ret == 1)
		return ;
	cpu->r.r_pc += 2;
}

void handler_93_call(cpu_t *cpu) {
	if (!can_acces_u8(cpu, cpu->r.r_pc + 1))
		return set_interrupt(cpu, CPU_INT_BADOPCODE);
	u8 info = get_u8(cpu, cpu->r.r_pc + 1);

	u8 reg = info & 0b1111;
	u8 cond = info >> 4;
	int ret = cpu_do_call(cpu, cpu->r.r_pc + *get_Uregister_ptr(cpu, reg), cond, cpu->r.r_pc + 2);
	if (ret == 2)
		return set_interrupt(cpu, CPU_INT_BADOPCODE);
	if (ret == -1)
		return set_interrupt(cpu, CPU_INT_OUT_BOUND);
	if (ret == 1)
		return ;
	cpu->r.r_pc += 2;
}

void handler_94_call(cpu_t *cpu) {
	if (!can_acces_u8(cpu, cpu->r.r_pc + 1))
		return set_interrupt(cpu, CPU_INT_BADOPCODE);
	u8 info = get_u8(cpu, cpu->r.r_pc + 1);

	u8 reg = info & 0b1111;
	u8 cond = info >> 4;

	u32 *reg_ptr = get_Uregister_ptr(cpu, reg);
	if (!can_acces_u32(cpu, *reg_ptr))
		return set_interrupt(cpu, CPU_INT_OUT_BOUND);
	u32 addr = get_u32(cpu, *reg_ptr) + cpu->r.r_pc;

	int ret = cpu_do_call(cpu, addr, cond, cpu->r.r_pc + 2);
	if (ret == 2)
		return set_interrupt(cpu, CPU_INT_BADOPCODE);
	if (ret == -1)
		return set_interrupt(cpu, CPU_INT_OUT_BOUND);
	if (ret == 1)
		return ;
	cpu->r.r_pc += 2;
}

void handler_95_call(cpu_t *cpu) {
	if (!can_acces_u8(cpu, cpu->r.r_pc + 1))
		return set_interrupt(cpu, CPU_INT_BADOPCODE);
	u8 info = get_u8(cpu, cpu->r.r_pc + 1);

	u8 reg = info & 0b1111;
	u8 cond = info >> 4;

	u32 *reg_ptr = get_Uregister_ptr(cpu, reg);
	if (!can_acces_u32(cpu, cpu->r.r_pc + *reg_ptr))
		return set_interrupt(cpu, CPU_INT_OUT_BOUND);
	u32 addr = get_u32(cpu, cpu->r.r_pc + *reg_ptr) + cpu->r.r_pc;

	int ret = cpu_do_call(cpu, addr, cond, cpu->r.r_pc + 2);
	if (ret == 2)
		return set_interrupt(cpu, CPU_INT_BADOPCODE);
	if (ret == -1)
		return set_interrupt(cpu, CPU_INT_OUT_BOUND);
	if (ret == 1)
		return ;
	cpu->r.r_pc += 2;
}

void handler_96_call(cpu_t *cpu) {
	if (!can_acces_u8(cpu, cpu->r.r_pc + 1))
		return set_interrupt(cpu, CPU_INT_BADOPCODE);
	u8 info = get_u8(cpu, cpu->r.r_pc + 1);
	if ((info & 0b11) != 0)
		return set_interrupt(cpu, CPU_INT_BADOPCODE);
	u8 TT = (info >> 2) &0b11;
	if (TT == 0b11)
		return set_interrupt(cpu, CPU_INT_BADOPCODE);
	u8 cond = info >> 4;
	if (!can_acces_u_with_size(cpu, cpu->r.r_pc + 2, TT))
		return set_interrupt(cpu, CPU_INT_BADOPCODE);
	u32 CONST = get_u_with_size(cpu, cpu->r.r_pc + 2, TT);
	u32 addr = cpu->r.r_pc + CONST;
	if (!can_acces_u32(cpu, addr))
		return set_interrupt(cpu, CPU_INT_OUT_BOUND);
	addr = get_u32(cpu, addr) + cpu->r.r_pc;

	int ret = cpu_do_call(cpu, addr, cond, cpu->r.r_pc + 2 + TYPE_SIZE(TT));
	if (ret == 2)
		return set_interrupt(cpu, CPU_INT_BADOPCODE);
	if (ret == -1)
		return set_interrupt(cpu, CPU_INT_OUT_BOUND);
	if (ret == 1)
		return ;
	cpu->r.r_pc += 2 + TYPE_SIZE(TT);
}



void handler_97_call(cpu_t *cpu) {
	if (!can_acces_u8(cpu, cpu->r.r_pc + 1))
		return set_interrupt(cpu, CPU_INT_BADOPCODE);
	u8 info = get_u8(cpu, cpu->r.r_pc + 1);
	if ((info & 0b11) != 0)
		return set_interrupt(cpu, CPU_INT_BADOPCODE);
	u8 TT = (info >> 2) &0b11;
	if (TT == 0b11)
		return set_interrupt(cpu, CPU_INT_BADOPCODE);
	u8 cond = info >> 4;
	if (!can_acces_u_with_size(cpu, cpu->r.r_pc + 2, TT))
		return set_interrupt(cpu, CPU_INT_BADOPCODE);
	u32 CONST = get_u_with_size(cpu, cpu->r.r_pc + 2, TT);
	u32 addr = CONST + cpu->r.r_pc;

	int ret = cpu_do_call(cpu, addr, cond, cpu->r.r_pc + 2 + TYPE_SIZE(TT));
	if (ret == 2)
		return set_interrupt(cpu, CPU_INT_BADOPCODE);
	if (ret == -1)
		return set_interrupt(cpu, CPU_INT_BADOPCODE);
	if (ret == 1)
		return ;
	cpu->r.r_pc += 2 + TYPE_SIZE(TT);

}

void handler_98_call(cpu_t *cpu) {
	if (!can_acces_u8(cpu, cpu->r.r_pc + 1))
		return set_interrupt(cpu, CPU_INT_BADOPCODE);
	u8 info = get_u8(cpu, cpu->r.r_pc + 1);

	u8 reg = info & 0b1111;
	u8 cond = info >> 4;
	u32 *reg_ptr = get_Uregister_ptr(cpu,  reg);
	if (!can_acces_u32(cpu, cpu->r.r_pc +  *reg_ptr))
		return set_interrupt(cpu, CPU_INT_OUT_BOUND);

	u32 addr = get_u32(cpu, cpu->r.r_pc + *reg_ptr);

	int ret = cpu_do_call(cpu, addr, cond, cpu->r.r_pc + 2);
	if (ret == 2)
		return set_interrupt(cpu, CPU_INT_BADOPCODE);
	if (ret == -1)
		return set_interrupt(cpu, CPU_INT_OUT_BOUND);
	if (ret == 1)
		return ;
	cpu->r.r_pc += 2;
}

void handler_99_call(cpu_t *cpu) {
	if (!can_acces_u8(cpu, cpu->r.r_pc + 1))
		return set_interrupt(cpu, CPU_INT_BADOPCODE);
	u8 info = get_u8(cpu, cpu->r.r_pc + 1);

	if ((info &  0b11) != 0)
		return set_interrupt(cpu, CPU_INT_BADOPCODE);
	u8 TT = (info >> 2) & 0b11;
	if (!can_acces_u_with_size(cpu, cpu->r.r_pc + 2, TT))
		return set_interrupt(cpu, CPU_INT_BADOPCODE);
	u8 cond = info >> 4;
	u32 CONST = get_u_with_size(cpu, cpu->r.r_pc + 2, TT);
	u32 addr = CONST + cpu->r.r_pc;
	if (!can_acces_u32(cpu, addr))
		return set_interrupt(cpu, CPU_INT_OUT_BOUND);
	addr = get_u32(cpu, addr);
	int ret = cpu_do_call(cpu, addr, cond, cpu->r.r_pc + 2 + TYPE_SIZE(TT));
	if (ret == 2)
		return set_interrupt(cpu, CPU_INT_BADOPCODE);
	if (ret == -1)
		return set_interrupt(cpu, CPU_INT_OUT_BOUND);
	if (ret == 1)
		return ;
	cpu->r.r_pc += 2 + TYPE_SIZE(TT);
}