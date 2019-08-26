# Instruction Memory
1. Aumentar a 1024 instrucciones (4096 bytes)
2. Direccionamiento virtual
  0x400000 - 0x401000
3. Circuito PCDecoder
  Entrada (Virtual PC)
  Salidas (Physical PC, Invalid PC)

# Data Memory
1. Stack (1024 palabras = 4096 bytes)
2. Global (1024 palabras = 4096 bytes)
3. Direccionamiento virtual global
  0x10010000 - 0x10011000
4. Direccionamiento virtual stack
  0x7FFFEFFC - 0x7FFFFFFC
5. Circuito MemoryDecoder
  Entrada (Virtual address)
  Salida (Physical address, Invalid data address)
  
# New instructions
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