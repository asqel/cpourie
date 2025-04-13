/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ld.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlleres <axlleres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 00:37:39 by axlleres          #+#    #+#             */
/*   Updated: 2025/04/13 21:27:45 by axlleres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cpu.h"
#include "memory.h"

void handler_6c_ld(cpu_t *cpu)
{
	if (!can_acces_u8(cpu, cpu->r.r_pc + 1))
		return set_interrupt(cpu, CPU_INT_BADOPCODE);

	u8 infos = get_u8(cpu, cpu->r.r_pc + 1);

	u8 dest = infos >> 4;
	u8 type = (infos >> 2) & 0b11;
	if (type == 0b11)
		return set_interrupt(cpu, CPU_INT_BADOPCODE);
	u8 op = infos & 0b11;
	if (op == 0b11) {
		if (!can_acces_u_with_size(cpu, cpu->r.r_pc + 2, type))
			return set_interrupt(cpu, CPU_INT_BADOPCODE);

		u32 *reg = get_Uregister_ptr(cpu, dest);
		u32 val = get_u_with_size(cpu, cpu->r.r_pc + 2, type);
		*reg = val;
		cpu->r.r_pc += 2 + TYPE_SIZE(type);
		return ;
	}
	else if (op == 0b10) {
		if (!can_acces_u32(cpu, cpu->r.r_pc + 2))
			return set_interrupt(cpu, CPU_INT_BADOPCODE);

		u32 addr = get_u32(cpu, cpu->r.r_pc + 2);
		if (!can_acces_u_with_size(cpu, addr, type))
			return set_interrupt(cpu, CPU_INT_OUT_BOUND);

		u32 *reg = get_Uregister_ptr(cpu, dest);
		u32 val = get_u_with_size(cpu, addr, type);
		*reg = val;
		cpu->r.r_pc += 2 + sizeof(u32);
		return ;
	}
	set_interrupt(cpu, CPU_INT_BADOPCODE);
}

void handler_6a_ld(cpu_t *cpu) {
	if (!can_acces_u8(cpu, cpu->r.r_pc + 1))
		return set_interrupt(cpu, CPU_INT_OUT_BOUND);

	u8 infos = get_u8(cpu, cpu->r.r_pc + 1);
	u8 YY = infos >> 6;
	u8 TT = (infos >> 4) & 0b11;
	u8 reg = infos & 0b1111;
	if (YY == 0b11 || TT == 0b11)
		return set_interrupt(cpu, CPU_INT_BADOPCODE);
	if (!can_acces_u_with_size(cpu, cpu->r.r_pc + 2, YY))
		return set_interrupt(cpu, CPU_INT_OUT_BOUND);
	u32 addr = get_u_with_size(cpu, cpu->r.r_pc + 2, YY);
	addr += cpu->r.r_pc;
	if (!can_acces_u_with_size(cpu, addr, TT))
		return set_interrupt(cpu, CPU_INT_OUT_BOUND);

	u32 *reg_ptr = get_Uregister_ptr(cpu, reg);
	*reg_ptr = get_u_with_size(cpu, addr, TT);

	cpu->r.r_pc += 2 + TYPE_SIZE(YY);
}

void handler_60_ld(cpu_t *cpu) {
	if (!can_acces_u8(cpu, cpu->r.r_pc + 1))
		return set_interrupt(cpu, CPU_INT_OUT_BOUND);

	u8 infos = get_u8(cpu, cpu->r.r_pc + 1);
	u8 YY = infos >> 6;
	u8 TT = (infos >> 4) & 0b11;
	u8 reg = infos & 0b1111;
	if (YY == 0b11 || TT == 0b11)
		return set_interrupt(cpu, CPU_INT_BADOPCODE);
	if (!can_acces_u_with_size(cpu, cpu->r.r_pc + 2, YY))
		return set_interrupt(cpu, CPU_INT_OUT_BOUND);

	u32 addr = cpu->r.r_pc + get_u_with_size(cpu, cpu->r.r_pc + 2, YY);
	if (!can_acces_u32(cpu, addr))
		return set_interrupt(cpu, CPU_INT_OUT_BOUND);
	addr = get_u32(cpu, addr);
	if (!can_acces_u_with_size(cpu, addr, TT))
		return set_interrupt(cpu, CPU_INT_OUT_BOUND);

	u32 *reg_ptr = get_Uregister_ptr(cpu, reg);
	*reg_ptr = get_u_with_size(cpu, addr, TT);
	cpu->r.r_pc += 2 + TYPE_SIZE(YY);
}

void handler_6b_ld(cpu_t *cpu) {
	if (!can_acces_u16(cpu, cpu->r.r_pc + 1))
		return set_interrupt(cpu, CPU_INT_OUT_BOUND);

	u8 infos1 = get_u8(cpu, cpu->r.r_pc + 1);
	u8 infos2 = get_u8(cpu, cpu->r.r_pc + 2);

	u8 regA = infos1 & 0b1111;
	u8 regB = infos1 >> 4;
	if ((infos2 & 0b1) == 0) {
		if (((infos2 >> 1) & 0b111) != 0)
			return set_interrupt(cpu, CPU_INT_BADOPCODE);
		u8 TT = infos2 >> 6;
		u8 YY = (infos2 >> 4) & 0b11;
		if (TT == 0b11 || YY == 0b11)
			return set_interrupt(cpu, CPU_INT_OUT_BOUND);
		if (!can_acces_u_with_size(cpu, cpu->r.r_pc + 3, YY))
			return set_interrupt(cpu, CPU_INT_OUT_BOUND);

		u32 addr = cpu->r.r_pc + get_u_with_size(cpu, cpu->r.r_pc + 3, YY) + *get_Uregister_ptr(cpu, regB);
		if (!can_acces_u_with_size(cpu, addr, TT))
			return set_interrupt(cpu, CPU_INT_OUT_BOUND);
		*get_Uregister_ptr(cpu, regA) = get_u_with_size(cpu, addr, TT);
		cpu->r.r_pc += 3 + TYPE_SIZE(TT);
		return ;
	}
	if (((infos2 >> 1) & 0b11111) != 0)
		return set_interrupt(cpu, CPU_INT_BADOPCODE);
	u8 TT = infos2 >> 6;
	u32 addr = cpu->r.r_pc + *get_Uregister_ptr(cpu, regB);
	if (!can_acces_u32(cpu, addr))
		return set_interrupt(cpu, CPU_INT_OUT_BOUND);
	addr = get_u32(cpu, addr);
	if (!can_acces_u_with_size(cpu, addr, TT))
		return set_interrupt(cpu, CPU_INT_OUT_BOUND);
	*get_Uregister_ptr(cpu, regA) = get_u_with_size(cpu, addr, TT);
	cpu->r.r_pc += 3;
}

void handler_4c_ld(cpu_t *cpu) {
	if (!can_acces_u16(cpu, cpu->r.r_pc + 1))
		return set_interrupt(cpu, CPU_INT_BADOPCODE);

	u8 infos1 = get_u8(cpu, cpu->r.r_pc + 1);
	u8 infos2 = get_u8(cpu, cpu->r.r_pc + 2);
	u8 TT = (infos1 >> 2) & 0b11;
	if ((infos1 & 0b11) != 0 || (infos2 & 0b1111) != 0 || TT == 0b11)
		return set_interrupt(cpu, CPU_INT_BADOPCODE);

	u32 *regB = get_Uregister_ptr(cpu, infos1 >> 4);
	u32 *regA = get_Uregister_ptr(cpu, infos2 >> 4);
	if (!can_acces_u_with_size(cpu, *regB, TT))
		return set_interrupt(cpu, CPU_INT_OUT_BOUND);
	*regA = get_u_with_size(cpu, *regB, TT);

	cpu->r.r_pc += 3;
}