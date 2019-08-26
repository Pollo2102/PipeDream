
# Instruction Memory

1. [x] Aumentar a 1024 instrucciones (4096 bytes)

2. [x] Direccionamiento virtual

0x400000 - 0x401000

3. Circuito PCDecoder

- [x] Entrada (Virtual PC)

- [x] Salidas (Physical PC, Invalid PC)

# Data Memory

1. [x] Stack (1024 palabras = 4096 bytes)

2. [x] Global (1024 palabras = 4096 bytes)

3. [x] Direccionamiento virtual global

[x] 0x10010000 - 0x10011000

4. Direccionamiento virtual stack

[x] 0x7FFFEFFC - 0x7FFFFFFC

5. Circuito MemoryDecoder

[x] Entrada (Virtual address)

[x] Salida (Physical address, Invalid data address)

# New instructions (DONE)

* addu

* subu

* addi

* addiu

* andi

* ori

* lui

* xor

* xori

* slti

* sltu

* sltiu