#ifndef OPCODES_H
#define OPCODES_H

/*
push_XX_as_YY
0b0001xxyy ...(what to push)

XX / YY:
	u8			 | 00
	u16			 | 01
	u32			 | 10
	u48			 | 11
only for XX >= YY else badopcode

push_double: 0b00100000 ...(64bits)

*/

#define OPC_EXTEND 0b11111111

#define OPC_push_u8_as_u8  0b00010000
#define OPC_push_u8_as_u16 0b00010001
#define OPC_push_u8_as_u32 0b00010010
#define OPC_push_u8_as_u48 0b00010011

#define OPC_push_u16_as_u16 0b00010101
#define OPC_push_u16_as_u32 0b00010110
#define OPC_push_u16_as_u48 0b00010111

#define OPC_push_u32_as_u32 0b00011010
#define OPC_push_u32_as_u48 0b00011011

#define OPC_push_u48_as_u48 0b00011111
#define OPC_push_double     0b00100000

#define INST_U8_PARAM(X) (*((u8 *)(X + 1)))
#define INST_U16_PARAM(X) (*((u16 *)(X + 1)))
#define INST_U32_PARAM(X) (*((u32 *)(X + 1)))
#define INST_U48_PARAM(X) (*((u48 *)(X + 1)))

int do_opcode(cpu_t *cpu);

#endif