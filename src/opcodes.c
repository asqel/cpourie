#include "cpu.h"
#include "opcodes.h"
#include "memory.h"


typedef  void (*opcode_handler_t)(cpu_t *);

opcode_handler_t *opcodes_funcs = NULL;

void exit_opcode() {
	free(opcodes_funcs);
}

void init_opcodes() {
	if (opcodes_funcs == NULL)
	{
		atexit(exit_opcode);
		opcodes_funcs = calloc(256, sizeof(opcode_handler_t));
	}

	opcodes_funcs[0x6c] = &handler_6c_ld;
	opcodes_funcs[0x6a] = &handler_6a_ld;
	opcodes_funcs[0x60] = &handler_60_ld;
	opcodes_funcs[0x4c] = &handler_4c_ld;
	opcodes_funcs[0x73] = &handler_73_st;
	opcodes_funcs[0x53] = &handler_53_st;
	opcodes_funcs[0x6d] = &handler_6d_mov;
	opcodes_funcs[0x4d] = &handler_4d_mov;
	opcodes_funcs[0xa0] = &handler_a0_add;
	opcodes_funcs[0xa1] = &handler_a1_add;
	opcodes_funcs[0xa2] = &handler_a2_add;
	opcodes_funcs[0xa3] = &handler_a3_add;
	opcodes_funcs[0xa4] = &handler_a4_add;
	opcodes_funcs[0xa8] = &handler_a8_sub;
	opcodes_funcs[0xa9] = &handler_a9_sub;
	opcodes_funcs[0xaa] = &handler_aa_sub;
	opcodes_funcs[0xab] = &handler_ab_sub;
	opcodes_funcs[0xac] = &handler_ac_sub;
	opcodes_funcs[0xb0] = &handler_b0_imul;
	opcodes_funcs[0xb1] = &handler_b1_imul;
	opcodes_funcs[0xb2] = &handler_b2_umul;
	opcodes_funcs[0xb3] = &handler_b3_umul;
	opcodes_funcs[0xb4] = &handler_b4_idiv;
	opcodes_funcs[0xb5] = &handler_b5_udiv;
	opcodes_funcs[0xb6] = &handler_b6_imod;
	opcodes_funcs[0xb7] = &handler_b7_umod;
	opcodes_funcs[0x20] = &handler_20_band;
	opcodes_funcs[0x21] = &handler_21_band;
	opcodes_funcs[0x22] = &handler_22_bor;
	opcodes_funcs[0x23] = &handler_23_bor;
	opcodes_funcs[0x24] = &handler_24_not;
	opcodes_funcs[0x25] = &handler_25_bxor;
	opcodes_funcs[0x26] = &handler_26_bxor;
	opcodes_funcs[0x30] = &handler_30_land;
	opcodes_funcs[0x31] = &handler_31_lor;
	opcodes_funcs[0x32] = &handler_32_lnot;
	opcodes_funcs[0x33] = &handler_33_land;
	opcodes_funcs[0x34] = &handler_34_ulshift;
	opcodes_funcs[0x35] = &handler_35_ulshift;
	opcodes_funcs[0x34] = &handler_34_urshift;
	opcodes_funcs[0x35] = &handler_35_urshift;
	opcodes_funcs[0xc0] = &handler_c0_cmp;
	opcodes_funcs[0xc1] = &handler_c1_cmp;
	opcodes_funcs[0xc2] = &handler_c2_cmp;
	opcodes_funcs[0xc3] = &handler_c3_cmp;
	opcodes_funcs[0xc4] = &handler_c4_cmp;
	opcodes_funcs[0xc5] = &handler_c5_cmp;
	opcodes_funcs[0xc6] = &handler_c6_cmp;
	opcodes_funcs[0xc7] = &handler_c7_cmp;
	opcodes_funcs[0xc8] = &handler_c8_cmod;
	opcodes_funcs[0xc9] = &handler_c9_cmod;
	opcodes_funcs[0x80] = &handler_80_jmp;
	opcodes_funcs[0x81] = &handler_81_jmp;
	opcodes_funcs[0x82] = &handler_82_jmp;
	opcodes_funcs[0x83] = &handler_83_jmp;
	opcodes_funcs[0x84] = &handler_84_jmp;
	opcodes_funcs[0x85] = &handler_85_jmp;
	opcodes_funcs[0x86] = &handler_86_jmp;
	opcodes_funcs[0x87] = &handler_87_jmp;
	opcodes_funcs[0x88] = &handler_88_jmp;
	opcodes_funcs[0x89] = &handler_89_jmp;
	opcodes_funcs[0x90] = &handler_90_call;
	opcodes_funcs[0x91] = &handler_91_call;
	opcodes_funcs[0x92] = &handler_92_call;
	opcodes_funcs[0x93] = &handler_93_call;
	opcodes_funcs[0x94] = &handler_94_call;
	opcodes_funcs[0x95] = &handler_95_call;
	opcodes_funcs[0x96] = &handler_96_call;
	opcodes_funcs[0x97] = &handler_97_call;
	opcodes_funcs[0x98] = &handler_98_call;
	opcodes_funcs[0x99] = &handler_99_call;
	opcodes_funcs[0xe2] = &handler_e2_push;
	opcodes_funcs[0xe8] = &handler_e8_pop;
	opcodes_funcs[0xd0] = &handler_d0_swap;
	opcodes_funcs[0x8f] = &handler_8f_ret;
	opcodes_funcs[0xf0] = &handler_f0_setsdt;
	opcodes_funcs[0xf1] = &handler_f1_setddt;
	opcodes_funcs[0xf2] = &handler_f2_syscall;
	opcodes_funcs[0xf3] = &handler_f3_drivcall;
	opcodes_funcs[0xf4] = &handler_f4_sret;
	opcodes_funcs[0xf4] = &handler_f4_dret;
	opcodes_funcs[0xf6] = &handler_f6_set_umem;
	opcodes_funcs[0xf7] = &handler_f7_set_umem;
	opcodes_funcs[0xf8] = &handler_f8_set_lvl_sp;
	opcodes_funcs[0xf9] = &handler_f9_set_lvl_bp;
	opcodes_funcs[0xfa] = &handler_fa_set_lvl_stack_len;
	opcodes_funcs[0xfb] = &handler_fb_read_lvl_sp;
	opcodes_funcs[0xfb] = &handler_fb_read_lvl_bp;
	opcodes_funcs[0xfb] = &handler_fb_read_lvl_stack_len;
}


void do_opcode(cpu_t *cpu) {
	if (cpu->r.r_pc >= cpu->mem_size) {
		cpu->r.interrupt = CPU_INT_OUT_BOUND;
		return;
	}

	u8 opcode = cpu->memory[cpu->r.r_pc];

	if (opcodes_funcs[opcode] != NULL)
		opcodes_funcs[opcode](cpu);
	else
		cpu->r.interrupt = CPU_INT_BADOPCODE;
}
