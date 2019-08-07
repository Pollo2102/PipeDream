TARGET=screen.elf
C_SOURCES=main.c PipeDream.c
ASM_SOURCES=start.S functions.S
ASM_OUTPUT=$(TARGET).s
ASMGEN_SOURCES=$(C_SOURCES:.c=.S)
OBJ_FILES=$(ASM_SOURCES:.S=.o) $(ASMGEN_SOURCES:.S=.o) ../lib/libtinymips.a
GCC_ROOT=/opt/gcc-mips-9.1
LD=$(GCC_ROOT)/bin/mips-elf-ld
CC=$(GCC_ROOT)/bin/mips-elf-gcc
AS=$(GCC_ROOT)/bin/mips-elf-as
OBJDUMP=$(GCC_ROOT)/bin/mips-elf-objdump
CFLAGS=-I../include -G 0 -Os -Wall -ffreestanding -fno-stack-protector \
	   -nostdinc -nostdlib -fno-delayed-branch -fno-builtin
ELF_TO_MIF=../sim/elf2mif
IMEM_FILE=../sim/code.mif
DMEM_FILE=../sim/data.mif
IMEM_WORD_COUNT=2048
DMEM_WORD_COUNT=1024

.PHONY: clean run
.SUFFIXES:

all: mem_files $(ASM_OUTPUT)

mem_files: $(TARGET)
	$(ELF_TO_MIF) $^ $(IMEM_FILE) $(DMEM_FILE) $(IMEM_WORD_COUNT) $(DMEM_WORD_COUNT)
	> mem_files

$(TARGET): $(OBJ_FILES)
	$(LD) -G 0 -T link_script.ld -o $@ $^

%.S: %.c
	$(CC) $(CFLAGS) -S -mips1 -o $@ $<
	sed -i -e '/[ \t]*nop$$/d' $@

%.o: %.S
	$(CC) $(CFLAGS) -c -mips1 -o $@ $<

$(ASM_OUTPUT): $(TARGET)
	$(OBJDUMP) -D $< > $@

run: $(TARGET)
	cd ../sim/ && ./Mips32SocSim --mif code.mif:data.mif --font mif/font_rom.mif

clean:
	rm -f ${TARGET}
	rm -f *.o
	rm -f *.mif
	rm -f *.bin mem_files
	rm -f ${ASMGEN_SOURCES}
	rm -f ${ASM_OUTPUT}
