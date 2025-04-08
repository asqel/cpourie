#ifndef CPU_H
#define CPU_H

#include "types.h"

#define PCI_BASE 0x0ABC
#define PCI_NUM 32 // pci at index 0 is pci controller
#define PCI_SPAVE_LEN 4 * 4 // each pci is assign 4 u32

typedef void (*pci_callback_t)(cpu_t *cpu, u8 num, u32 addr);

typedef struct {
	pci_callback_t pci_callback_t[PCI_NUM];

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

	uint8_t interrupt;

	double r_red;
	double r_green;
	double r_blue;
	double r_magenta;
	double r_yellow;
	double r_cyan;
	double r_white;
	double r_black;
} registers_t;

typedef struct {
	registers_t r;
	u8 *memory;
	u32 mem_size;
	u8 is_halted;
} cpu_t;

cpu_t *new_cpu(u32 mem_size);
void free_cpu(cpu_t *cpu);

void dump_registers(cpu_t *cpu);


#define CPU_INT_BADOPCODE 0x01
#define CPU_INT_OUT_BOUND 0x02

#endif