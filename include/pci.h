#ifndef PCI_H
#define PCI_H

#include "cpu.h"

void init_pci(cpu_t *cpu);

// callback
void pci_printer_callback(cpu_t *cpu, cpu_pci_t *self);
void call_pcis(cpu_t *cpu);

#endif