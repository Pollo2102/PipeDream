OUTPUT_FORMAT("elf32-bigmips")
ENTRY(start)
SECTIONS
{
  .text 0x400000 :
  {
    *(.text*)    
  }

  _gp = 0x0;
  .sdata 0x0: 
  {
    *(.sdata)
  }
  .sbss :
  {
    *(.sbss)
  }
  
  .data 0x10010000 :
  {
    
    *(.rodata*)
    *(.data)
    *(.bss)
  }
  
  /DISCARD/ : 
  {
    *(.strtab)
    *(.rel.text)
    *(.mdebug.abi32)
    *(.pdr)
    *(.rel.pdr)
    *(.comment)
    *(.note.GNU-stack)
    *(.MIPS.abiflags)
    *(.reginfo)
    *(.rel.data)
  }
  . = ALIGN(4);
}