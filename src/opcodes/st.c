#include "cpu.h"

void handler_73_st(cpu_t *cpu) {
	if (!can_acces_u8(cpu, cpu->r.r_pc + 1))
		return set_interrupt(cpu, CPU_INT_BADOPCODE);
	if (!can_acces_u32(cpu, cpu->r.r_pc + 2))
		return set_interrupt(cpu, CPU_INT_BADOPCODE);

	u8 infos = get_u8(cpu, cpu->r.r_pc + 1);
	u32 addr = get_u32(cpu, cpu->r.r_pc + 2);

	u8 reg = infos >> 4;
	u8 TT = (infos >> 2) & 0b11;
	if (TT == 0b11)
		return set_interrupt(cpu, CPU_INT_BADOPCODE);
	u32 val = *get_Uregister_ptr(cpu, reg);
	u8 mod = infos & 0b11;
	if (mod == 0) {
		if (!can_acces_u_with_size(cpu, addr, TT))
			return set_interrupt(cpu, CPU_INT_OUT_BOUND);
		set_u_with_size(cpu, addr, val, TT);
		cpu->r.r_pc += 2 + sizeof(u32);
		return ;
	}
	else if (mod == 0b01) {
		addr += cpu->r.r_pc;
		if (!can_acces_u_with_size(cpu, addr, TT))
			return set_interrupt(cpu, CPU_INT_OUT_BOUND);
		set_u_with_size(cpu, addr, val, TT);
		cpu->r.r_pc += 2 + sizeof(u32);
		return ;
	}
	else if (mod == 0b10) {
		addr += cpu->r.r_pc;
		if (!can_acces_u32(cpu, addr))
			return set_interrupt(cpu, CPU_INT_OUT_BOUND);
		addr = get_u32(cpu, addr);
		if (!can_acces_u_with_size(cpu, addr, TT))
			return set_interrupt(cpu, CPU_INT_OUT_BOUND);
		set_u_with_size(cpu, addr, val, TT);
		cpu->r.r_pc += 2 + sizeof(u32);
		return ;
	}
	return set_interrupt(cpu, CPU_INT_BADOPCODE);
}

void handler_53_st(cpu_t *cpu) {
	if (!can_acces_u8(cpu, cpu->r.r_pc + 1))
		return set_interrupt(cpu, CPU_INT_BADOPCODE);

	u8 info1 = get_u8(cpu, cpu->r.r_pc + 1);
	u8 info1_mod = info1 >> 6;
	if (info1_mod == 0b11) {
		if (!can_acces_u8(cpu, cpu->r.r_pc + 2) || !can_acces_u32(cpu, cpu->r.r_pc + 3))
			return set_interrupt(cpu, CPU_INT_BADOPCODE);
		u8 info2 = get_u8(cpu, cpu->r.r_pc + 2);
		if ((info2 & 0b1111) != 0)
			return set_interrupt(cpu, CPU_INT_BADOPCODE);
		u32 addr = get_u32(cpu, cpu->r.r_pc + 3);
		u8 TT = info1 & 0b11;
		if (TT == 0b11)
			return set_interrupt(cpu, CPU_INT_BADOPCODE);
		u8 regA = (info1 >> 2) & 0b1111;
		u8 regB = info2 >> 4;
		addr += *get_Uregister_ptr(cpu, regB);
		if (!can_acces_u_with_size(cpu, addr, TT))
			return set_interrupt(cpu, CPU_INT_OUT_BOUND);
		set_u_with_size(cpu, addr, TT, *get_Uregister_ptr(cpu, regA));
		cpu->r.r_pc += 3 + sizeof(u32);
		return ;
	}
	if (info1_mod ==  0b10) {
		if (!can_acces_u8(cpu, cpu->r.r_pc + 2))
			return set_interrupt(cpu, CPU_INT_BADOPCODE);
		u8 info2 = get_u8(cpu, cpu->r.r_pc + 2);
		u8 info2_mod = info2 & 0b11;
		u8 TT = info1 & 0b11;
		u8 regB = (info1 >> 2) & 0b1111;
		u8 YY = info2 >> 6;
		u8 regA = (info2 >> 2) & 0b1111;
		if (info2_mod == 0b00 && regA == 0) {
			if (!can_acces_u_with_size(cpu, cpu->r.r_pc + 3, TT))
				return set_interrupt(cpu, CPU_INT_OUT_BOUND);
			if (!can_acces_u_with_size(cpu, cpu->r.r_pc + 3 + TYPE_SIZE(TT), YY))
				return set_interrupt(cpu, CPU_INT_OUT_BOUND);
			u32 CONST2 = get_u_with_size(cpu, cpu->r.r_pc + 3, TT);
			u32 CONST1 = get_u_with_size(cpu, cpu->r.r_pc + 3 + TYPE_SIZE(TT), YY);
			u32 addr = *get_Uregister_ptr(cpu, regB) + CONST1;
			if (!can_acces_u_with_size(cpu, addr, TT))
				return set_interrupt(cpu, CPU_INT_OUT_BOUND);
			set_u_with_size(cpu, addr, TT, CONST2);
			cpu->r.r_pc += 3 + TYPE_SIZE(TT) + TYPE_SIZE(YY);
			return ;
		}
		else if (info2_mod == 0b11) {
			if (!can_acces_u_with_size(cpu, cpu->r.r_pc + 3, YY))
				return set_interrupt(cpu, CPU_INT_BADOPCODE);
			u32 addr = cpu->r.r_pc + *get_Uregister_ptr(cpu, regB) + get_u_with_size(cpu, cpu->r.r_pc + 3,  YY);
			if (!can_acces_u_with_size(cpu, addr, TT))
				return set_interrupt(cpu, CPU_INT_OUT_BOUND);
			set_u_with_size(cpu, addr, TT, *get_Uregister_ptr(cpu, regA));
			cpu->r.r_pc += 3 + TYPE_SIZE(YY);
			return ;
		}
		else if (info2_mod == 0b10) {
			if (!can_acces_u_with_size(cpu, cpu->r.r_pc + 3, TT))
				return set_interrupt(cpu, CPU_INT_OUT_BOUND);
			if (!can_acces_u_with_size(cpu, cpu->r.r_pc + 3 + TYPE_SIZE(TT), YY))
				return set_interrupt(cpu, CPU_INT_OUT_BOUND);
			u32 CONST2 = get_u_with_size(cpu, cpu->r.r_pc + 3, TT);
			u32 CONST1 = get_u_with_size(cpu, cpu->r.r_pc + 3 + TYPE_SIZE(TT), YY);
			u32 addr = *get_Uregister_ptr(cpu, regB) + CONST1 + cpu->r.r_pc;
			if (!can_acces_u_with_size(cpu, addr, TT))
				return set_interrupt(cpu, CPU_INT_OUT_BOUND);
			set_u_with_size(cpu, addr, TT, CONST2);
			cpu->r.r_pc += 3 + TYPE_SIZE(TT) + TYPE_SIZE(YY);
			return ;
		}
	}
	else if (info1_mod == 0b01) {
		u8 regB = (info1 >> 2) & 0b1111;
		u8 TT = info1  & 0b11;
		if (!can_acces_u_with_size(cpu, cpu->r.r_pc + 2, TT))
			return set_interrupt(cpu, CPU_INT_BADOPCODE);
		u32 CONST = get_u_with_size(cpu, cpu->r.r_pc + 2, TT);
		u32 addr = cpu->r.r_pc + *get_Uregister_ptr(cpu, regB);
		if (!can_acces_u32(cpu, addr))
			return set_interrupt(cpu, CPU_INT_OUT_BOUND);
		addr = get_u32(cpu, addr);
		if (!can_acces_u_with_size(cpu, addr, TT))
			return set_interrupt(cpu, CPU_INT_OUT_BOUND);
		set_u_with_size(cpu, addr, TT, CONST);
		cpu->r.r_pc += 2 + TYPE_SIZE(TT);
		return ;
	}
	else if (info1_mod == 0b00) {
		u8 regB = (info1 >> 2) & 0b1111;
		u8 TT = info1  & 0b11;
		if (!can_acces_u8(cpu, cpu->r.r_pc + 3))
			return set_interrupt(cpu, CPU_INT_BADOPCODE);
		u8 info2 = get_u8(cpu, cpu->r.r_pc + 3);
		if ((info2 & 0b1111) == 0)
			return set_interrupt(cpu, CPU_INT_BADOPCODE);
		u8 regA = info2 >> 4;
		u32 addr = cpu->r.r_pc + *get_Uregister_ptr(cpu, regB);
		if (!can_acces_u32(cpu, addr))
			return set_interrupt(cpu, CPU_INT_OUT_BOUND);
		addr = get_u32(cpu, addr);
		if (!can_acces_u_with_size(cpu, addr, TT))
			return set_interrupt(cpu, CPU_INT_OUT_BOUND);
		set_u_with_size(cpu, addr, TT, *get_Uregister_ptr(cpu, regA));
		cpu->r.r_pc += 3;
		return ;
	}
	return set_interrupt(cpu, CPU_INT_BADOPCODE);
}