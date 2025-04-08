# **Instruction : `ldi` (Load Immediate)**

## **Description**
The `ldi` load an immediate value `V` into register `R`. the size of `V` depends on `T` :

| Type (`T`)  | size of `V` |
|-------------|--------------|
| `0b00` (u8)  | 1 octet |
| `0b01` (u16) | 2 octets |
| `0b10` (u32) | 4 octets |

---

## **Opcode & Format**

The instruction is encoded on 2 bytes followed by `V`

| **Fields**  | **Taille**  | **Description** |
|------------|------------|-----------------|
| `opcode`   | 1 Byte     | 0x01 (ldi)      |
| `info`     | 1 Byte     | 0bTTRRRR00 (TT = type of `V`, RRRR = register) |
| `V`        | Variable   | Immediate value |

### **Bits encoding**

#### **info**

|   7   |   6   |   5   |   4   |   3   |   2   |   1   |   0   |
|-------|-------|-------|-------|-------|-------|-------|-------|
|  T    |  T    |  R    |  R    |  R    |    R  |    0  |    0  |


### Type (`T`) `TT`

| **Value**      | **Description**               |
|----------------|-------------------------------|
| `0b00` (u8)     | 8 bits value                 |
| `0b01` (u16)    | 16 bit value                 |
| `0b10` (u32)    | 32 bit value                 |
| `0b11` (INVALIDE) | Invalide opcode            |

### **Registers (`R`)** `RRR`

| **Value** | **Name** |
|--------------|-----|
| `0b0000` | do |
| `0b0001` | do$ |
| `0b0010` | re |
| `0b0011` | re$ |
| `0b0100` | mi |
| `0b0101` | fa |
| `0b0110` | fa$ |
| `0b0111` | so |
| `0b1000` | so$ |
| `0b1001` | la |
| `0b1010` | la$ |
| `0b1011` | si |
| `0b1100` | in |
| `0b1101` | ou |
| `0b1110` | sp |
| `0b1111` | bp |

---

## **Examples**

### **Load `0x34` into `mi` (u8)**
```
ldi mi, 0x34
```

**Encoding :**
```
0b00000001 0b00010000 0x34
```

### **Load `0x1234` into `mi` (u16)**
```
ldi mi, 0x1234
```

**Encoding :**
```
0b00000001 0b01010000 0x34 0x12
```

### **Load `0x12345678` into `mi` (u32)**
```
ldi mi, 0x12345678
```

**Encoding :**
```
0b00000001 0b01110000 0x12 0x34 0x56 0x78
```

---

## **Intruction size**

| Type (`T`)  | Total size |
|-------------|------------------------|
| `0b00` (u8)  | 3 |
| `0b01` (u16) | 4 |
| `0b10` (u32) | 6 |
