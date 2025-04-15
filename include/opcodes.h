#ifndef OPCODES_H
#define OPCODES_H

#include "cpu.h"

void init_opcodes();
void do_opcode(cpu_t *cpu);

void handler_6c_ld(cpu_t *cpu);
void handler_6a_ld(cpu_t *cpu);
void handler_60_ld(cpu_t *cpu);
void handler_4c_ld(cpu_t *cpu);

void handler_73_st(cpu_t *cpu);
void handler_53_st(cpu_t *cpu);

void handler_6d_mov(cpu_t *cpu);
void handler_4d_mov(cpu_t *cpu);

void handler_a0_add(cpu_t *cpu);
void handler_a1_add(cpu_t *cpu);
void handler_a2_add(cpu_t *cpu);
void handler_a3_add(cpu_t *cpu);
void handler_a4_add(cpu_t *cpu);

void handler_a8_sub(cpu_t *cpu);
void handler_a9_sub(cpu_t *cpu);
void handler_aa_sub(cpu_t *cpu);
void handler_ab_sub(cpu_t *cpu);
void handler_ac_sub(cpu_t *cpu);

void handler_b0_imul(cpu_t *cpu);
void handler_b1_imul(cpu_t *cpu);
void handler_b2_umul(cpu_t *cpu);
void handler_b3_umul(cpu_t *cpu);

void handler_b4_idiv(cpu_t *cpu);
void handler_b5_udiv(cpu_t *cpu);

void handler_b6_imod(cpu_t *cpu);
void handler_b7_umod(cpu_t *cpu);

void handler_20_band(cpu_t *cpu);
void handler_21_band(cpu_t *cpu);
void handler_22_bor(cpu_t *cpu);
void handler_23_bor(cpu_t *cpu);
void handler_24_not(cpu_t *cpu);
void handler_25_bxor(cpu_t *cpu);
void handler_26_bxor(cpu_t *cpu);

void handler_30_land(cpu_t *cpu);
void handler_31_lor(cpu_t *cpu);
void handler_32_lnot(cpu_t *cpu);
void handler_33_land(cpu_t *cpu);

void handler_34_ulshift(cpu_t *cpu);
void handler_35_ulshift(cpu_t *cpu);
void handler_34_urshift(cpu_t *cpu);
void handler_35_urshift(cpu_t *cpu);

void handler_c0_cmp(cpu_t *cpu);
void handler_c1_cmp(cpu_t *cpu);
void handler_c2_cmp(cpu_t *cpu);
void handler_c3_cmp(cpu_t *cpu);
void handler_c4_cmp(cpu_t *cpu);
void handler_c5_cmp(cpu_t *cpu);
void handler_c6_cmp(cpu_t *cpu);
void handler_c7_cmp(cpu_t *cpu);

void handler_c8_cmod(cpu_t *cpu);
void handler_c9_cmod(cpu_t *cpu);

void handler_80_jmp(cpu_t *cpu);
void handler_81_jmp(cpu_t *cpu);
void handler_82_jmp(cpu_t *cpu);
void handler_83_jmp(cpu_t *cpu);
void handler_84_jmp(cpu_t *cpu);
void handler_85_jmp(cpu_t *cpu);
void handler_86_jmp(cpu_t *cpu);
void handler_87_jmp(cpu_t *cpu);
void handler_88_jmp(cpu_t *cpu);
void handler_89_jmp(cpu_t *cpu);

void handler_90_call(cpu_t *cpu);
void handler_91_call(cpu_t *cpu);
void handler_92_call(cpu_t *cpu);
void handler_93_call(cpu_t *cpu);
void handler_94_call(cpu_t *cpu);
void handler_95_call(cpu_t *cpu);
void handler_96_call(cpu_t *cpu);
void handler_97_call(cpu_t *cpu);
void handler_98_call(cpu_t *cpu);
void handler_99_call(cpu_t *cpu);

void handler_e2_push(cpu_t *cpu);
void handler_e8_pop(cpu_t *cpu);

void handler_d0_swap(cpu_t *cpu);

void handler_8f_ret(cpu_t *cpu);
void handler_f0_setsdt(cpu_t *cpu);
void handler_f1_setddt(cpu_t *cpu);
void handler_f2_syscall(cpu_t *cpu);
void handler_f3_drivcall(cpu_t *cpu);
void handler_f4_sret(cpu_t *cpu);
void handler_f4_dret(cpu_t *cpu);

void handler_f6_set_umem(cpu_t *cpu);
void handler_f7_set_umem(cpu_t *cpu);
void handler_f8_set_lvl_sp(cpu_t *cpu);
void handler_f9_set_lvl_bp(cpu_t *cpu);
void handler_fa_set_lvl_stack_len(cpu_t *cpu);
void handler_fb_read_lvl_sp(cpu_t *cpu);
void handler_fb_read_lvl_bp(cpu_t *cpu);
void handler_fb_read_lvl_stack_len(cpu_t *cpu);

#endif