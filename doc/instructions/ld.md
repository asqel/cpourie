# **ld**

## **General description**
Load to a register a constant value or a value from memory

## **General encoding**
| **Field** | **Bits** | **description** |
|-----------|----------|-----------------|
|  Opcode   |  0x01    | Opcode of ld    |
|  infos    | XXXXXXXX | information     |
|  ...      | ...      | additional bytes|



## **Opcode**
`0x01 | 0b00000001 | 1`

##  **ld R, X:T (Integer)**

### **Description**
Load a constant value `X` of type `T` into register `R`

| `T` | size of `X`| size of ld |
|-----|------------|------------|
|0b00 | 1          | 3          |
|0b01 | 2          | 4          |
|0b10 | 4          | 6          |
|0b11 | INVALID    | INAVLID    |

### **Encoding**

| **Fields** | **size**   | **Description**  |
|------------|------------|------------------|
| `opcode`   | 1 Byte     | 0x01 (ld)        |
| `info`     | 1 Byte     | infos of R and T |
| `X`        | Variable   | Contant value    |

#### `infos`

|   7   |   6   |   5   |   4   |   3   |   2   |   1   |   0   |
|-------|-------|-------|-------|-------|-------|-------|-------|
|  `T`  |  `T`  |  `R`  |  `R`  |  `R`  |  `R`  |   0   |   0   |

#### `X`
X is a value in little endian

## **ld, R, D (Double)**

