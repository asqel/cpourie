#include "cpu.h"
#include "pci.h"
#include <string.h>

void init_pci(cpu_t *cpu) {
	memset(&cpu->memory[PCI_BASE], 0, PCI_NUM * PCI_SPACE_LEN);

	for (int i = 0; i < PCI_NUM; i++) {
		cpu->pcis[i].addr_space = PCI_BASE + i * PCI_SPACE_LEN;
		cpu->pcis[i].idx = i;
		cpu->pcis[i].name = NULL;
		cpu->pcis[i].callback = NULL;
	}

	cpu->pcis[0].name = "PCI Controller";
	cpu->pcis[0].callback = NULL;

	cpu->pcis[1].name = "Printer";
	cpu->pcis[1].callback = pci_printer_callback;
}

void call_pcis(cpu_t *cpu) {
	for (int i = 0; i < PCI_NUM; i++) {
		if (cpu->pcis[i].callback != NULL) {
			cpu->pcis[i].callback(cpu, &cpu->pcis[i]);
		}
	}
}