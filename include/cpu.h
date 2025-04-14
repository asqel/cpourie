#ifndef CPU_H
#define CPU_H

#include "types.h"

#define PCI_BASE 0x0ABC
#define PCI_NUM 32 // pci at index 0 is pci controller
#define PCI_SPAVE_LEN 4 * 4 // each pci is assign 4 u32

struct cpu_t;
struct cpu_pci_t;

typedef void (*pci_callback_t)(struct cpu_t *cpu, struct cpu_pci_t *self);

typedef struct cpu_pci_t{
	u32 addr;
	u8 idx;
	char *name;
	pci_callback_t callback;
} cpu_pci_t;

typedef struct {

	u32 r_do;
	u32 r_do$;
	u32 r_re;
	u32 r_re$;
	u32 r_mi;
	u32 r_fa;
	u32 r_fa$;
	u32 r_so;
	u32 r_so$;
	u32 r_la;
	u32 r_la$;
	u32 r_si;
	u32 r_in; // instrument
	u32 r_ou; // outstrument (what ?)
	u32 r_sp;
	u32 r_bp;

	u32 r_pc;
	u32 r_status;
	u8  level; // 0 user, 1 trusted, 2 kernel

	u8 interrupt;
	u32 int_info1;
	u32 int_info2;

	double r_red;
	double r_green;
	double r_blue;
	double r_magenta;
	double r_yellow;
	double r_cyan;
	double r_white;
	double r_black;
} registers_t;
/*
status bits
0 : mod flag (a%b != 0)
1 : unsigned less
2 : unsigned greater
3 : equal
4 : signed less
5 : signed greater
*/

#define CPU_STAT_mod(X) ((X).r.r_status & 1)
#define CPU_STAT_Uless(X) (((X).r.r_status >> 1) & 1)
#define CPU_STAT_Ugreater(X) (((X).r.r_status >> 2) & 1)
#define CPU_STAT_equal(X) (((X).r.r_status >> 3) & 1)
#define CPU_STAT_Iless(X) (((X).r.r_status >> 4) & 1)
#define CPU_STAT_Igreater(X) (((X).r.r_status >> 5) & 1)

typedef struct {
	registers_t r;
	u8 *memory;
	u32 mem_size;
	u8 is_halted;
	cpu_pci_t pcis[PCI_NUM];
} cpu_t;

#define TYPE_SIZE(X) (((u32 [4]){1, 2, 4, 0})[X])
#define TYPE_MASK(X) (((u32 [4]){0xFF, 0xFFFF, 0xFFFFFFFF, 0})[X])

cpu_t *new_cpu(u32 mem_size);
void free_cpu(cpu_t *cpu);

void set_interrupt(cpu_t *cpu, u8 interrupt);

void dump_registers(cpu_t *cpu);

int can_acces_u8(cpu_t *cpu, u32 addr);
int can_acces_u16(cpu_t *cpu, u32 addr);
int can_acces_u32(cpu_t *cpu, u32 addr);
int can_acces_u32(cpu_t *cpu, u32 addr);
u32 get_u8(cpu_t *cpu, u32 addr);
u32 get_u16(cpu_t *cpu, u32 addr);
u32 get_u32(cpu_t *cpu, u32 addr);
u32 get_u32(cpu_t *cpu, u32 addr);
u32 get_u_with_size(cpu_t *cpu, u32 addr, u8 size);
i32 get_i_with_size(cpu_t *cpu, u32 addr, u8 size);
int can_acces_u_with_size(cpu_t *cpu, u32 addr, u8 size);

void set_u_with_size(cpu_t *cpu, u32 addr, u8 size, u32 val);
void set_u32(cpu_t *cpu, u32 addr, u32 val);
void set_u16(cpu_t *cpu, u32 addr, u16 val);
void set_u8(cpu_t *cpu, u32 addr, u8 val);

u32 *get_Uregister_ptr(cpu_t *cpu, u8 reg);
i32 *get_Iregister_ptr(cpu_t *cpu, u8 reg);

void update_status_comp(cpu_t *cpu, u32 a, u32 b);
void update_status_mod(cpu_t *cpu, u32 a, u32 b); // it doesn't check if b == 0


int cpu_push_u32(cpu_t *cpu, u32 val);
int cpu_push_u16(cpu_t *cpu, u16 val);
int cpu_push_u8(cpu_t *cpu, u8 val);
int cpu_push_u_with_size(cpu_t *cpu, u32 val, u8 type);

int cpu_do_jump(cpu_t *cpu, u32 addr, u8 cond);
int cpu_do_call(cpu_t *cpu, u32 addr, u8 cond, u32 ret_addr);

#define CPU_INT_BADOPCODE 0x01
#define CPU_INT_OUT_BOUND 0x02
#define CPU_INT_DIV_ZERO 0x03
#define CPU_INT_MOD_ZERO 0x04

#define CPU_COND_Uless 0x0
#define CPU_COND_Ugreater 0x1
#define CPU_COND_equal 0x2
#define CPU_COND_Iless 0x3
#define CPU_COND_Igreater 0x4
#define CPU_COND_Uless_eq 0x5
#define CPU_COND_Ugreater_eq 0x6
#define CPU_COND_Iless_eq 0x7
#define CPU_COND_Igreater_eq 0x8
#define CPU_COND_True 0x9
#define CPU_COND_mod0 0xA
#define CPU_COND_mod1 0xB

#endif