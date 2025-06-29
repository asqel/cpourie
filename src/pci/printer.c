#include "pci.h"

/*
BASE + 0: command register
BASE + 1: arg0
BASE + 2: arg2
BASE + 3: arg3
BASE + 4: status register
*/

#define CMD_PRINT 0xAA // arg0: char to print
#define CMD_CLEAR 0xAB
#define CMD_FLUSH 0xAC

void pci_printer_callback(cpu_t *cpu, cpu_pci_t *self) {
	u8 *base = &cpu->memory[self->addr_space];

	if (base[0] == 0)
		return ;
	if (base[0] == CMD_PRINT) {
		u8 c = base[1];
		if (c == 0)
			return ;
		putchar(c);
	}
	else if (base[0] == CMD_CLEAR)
		fwrite("\033[H\033[J", 1, 6, stdout);
	else if (base[0] == CMD_FLUSH)
		fflush(stdout);
	else
		base[4] = 1;
}
